#include <iostream>
#include "json.h"
#include "HttpSession.hpp"
#include "FaceDetectEvent.hpp"
#include "FaceDetectProcessor.hpp"
#include <fstream>
#include <ctime>
#include <string>

FaceDetectProcessor::FaceDetectProcessor() : GetImageEngine(){
    
}
FaceDetectProcessor::~FaceDetectProcessor(){
    
}
void FaceDetectProcessor::process(const std::string& ipcamera, const std::string& username, const std::string& userpwd) {
    std::string ipCam = ipcamera;
    std::cout << "ipcamera = " << ipcamera << std::endl;
    this->access_token = GetImageEngine::get_Token(ipcamera, username, userpwd);
      /**/
        // std::vector<std::string> _eventId_string;
        // std::vector<int> _eventId;
        int lastId = 1;
        std::ifstream file1;
        // std::string line;
        file1.open("../Data_EventId/" + ipcamera + "/facedetect.txt", std::ios::in);
        if(file1.is_open()){
            file1 >> lastId;
            std::cout << "lastId = " << lastId <<std::endl; 
            // while (getline(file1,line)){
            //     std::cout << "line = " << line << std::endl;
            //     _eventId_string.push_back(line); 
            // }
        }
        file1.close();
        // if (_eventId_string.size()==0){
        //     std::string line = "1";
        //     _eventId_string.push_back(line);
        // }
        // for (int i=0; i < _eventId_string.size(); i++){
        //     int num = atoi(_eventId_string.at(i).c_str());
        //     _eventId.push_back(num);
        // }
        // std::cout << "size_eventId_string = " << _eventId_string.size()<< std::endl;
        // std::cout << "size_eventId = " << _eventId.size()<< std::endl;
        // /**/
    std::string urlJson = "http://" + ipCam + ":4003/event/facedetect?lastId=" + std::to_string(lastId) + "&count=300";
    std::string urlFrame = "http://"+ ipCam + ":4003/event/frame/facedetect/";
    HttpSession* jsonSession = new HttpSession();
    std::fstream myfile;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timer[70];
    sprintf(timer, "%02d:%02d:%02d:%02d:%02d:%02d", ltm->tm_mday,ltm->tm_mon + 1,ltm->tm_year + 1900 ,ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    std::string Time= std::string(timer);
    // std::string day = std::to_string(ltm->tm_mday) + "-" + std::to_string(ltm->tm_mon);
    //
    std::string path = "../Json_Event/" + ipcamera + "/facedetect.txt";
    //
    jsonSession->setUrl(urlJson);
    jsonSession->addHeader("Content-Type: application/json");
    jsonSession->start();

    try {
        std::string message((const char *)jsonSession->getData(), jsonSession->getSize());
        auto j = json::parse(message);
        myfile.open(path, std::ios::out | std::ios::app);
        if (myfile.is_open()){
        myfile << Time;
        myfile << "\n";    
        myfile << message;
        myfile << "\n"; 
        }
        myfile.close();
        if (message != "[]"){
            for (auto event : j) {
                int monitorId = event["monitor_id"];
                auto jlocations = event["locations"];
                std::vector<cv::Rect> boxes;
                for (auto jlocation : jlocations) {
                    cv::Rect box(jlocation[0], jlocation[1], jlocation[2], jlocation[3]);
                    boxes.push_back(box);
                }

                // auto jdistances = event["distancing"];
                // std::vector<std::vector<float>> distances;
                // for(auto jdistance : jdistances) {
                //     std::vector<float> distance;
                //     for (auto id : jdistance) {
                //         distance.push_back(id);
                //     }
                //     distances.push_back(distance);
                // }

                std::string time = event["time"];
                /**/
                int eventId = event["eventId"];
                std::cout << "eventId = "<<eventId << std::endl;
                /**/
                time.replace(time.find(" "), 1, "_");
                // int frame = event["frame"];
                // /**/
                // int condition = comparison_facedetect(_eventId, eventId);
                // std::cout << "condition = " << condition << std::endl;
                // /**/
                // if (condition == 2){
                    std::cout << "--------Face Detect Event-------" << std::endl;
                    FaceDetectEvent* newEvent = new FaceDetectEvent(monitorId, boxes, time, eventId, ipcamera);
                    std::string currentFrameUrl = urlFrame +  std::to_string(eventId);
                    HttpSession* imageSession = new HttpSession();
                    imageSession->addHeader("Content-Type: image/jpeg");
                    imageSession->setUrl(currentFrameUrl);
                    imageSession->start();
                    try {
                        std::string dataImage((const char *)imageSession->getData(), imageSession->getSize());
                        std::vector<uchar> uImage(dataImage.begin(), dataImage.end());
                        cv::Mat image = cv::imdecode(uImage, cv::IMREAD_COLOR);
                        std::cout << "---------------imdecode image ---------------"<< std::endl;
                        newEvent->update(image);
                    }
                    catch(const std::exception& e) {
                        std::cerr << e.what() << '\n';
                    }
                    delete imageSession;
                    delete newEvent;
                // }
            }
            /**/
            std::ofstream file;
            file.open("../Data_EventId/" + ipcamera + "/facedetect.txt");
                // for (auto time : j){
                //     int eventIds = time["eventId"];
                //     // std::string times = time["time"];
                    if(file.is_open()){
                        file << j[j.size()-1]["eventId"] << std::endl;
                        std::cout << j[j.size()-1]["eventId"] << std::endl;
                    }   
                // }
            file.close(); 
            /**/ 
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "Process Events Successfull" << std::endl;
    delete jsonSession;
}
