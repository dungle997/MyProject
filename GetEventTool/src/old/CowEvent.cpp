//
//  CowEvent.cpp
//  CamHub
//
//  Created by Pham Quang Hoa on 19/02/2020.
//  Copyright © 2020 Pham Quang Hoa. All rights reserved.
//
// #include <iostream>
#include "CowEvent.hpp"


CowEvent::CowEvent(int cameraId, const std::vector<cv::Rect>& boxes, const std::string& time, int frame, std::string ipcamera) {
    this->cameraId = cameraId;
    this->boxes = boxes;
    this->time = time;
    this->ipcamera = ipcamera;
    this->frame = frame;
    std::cout << "Add Cow event with Cow: " << this->boxes.size() << std::endl;
    
}

CowEvent::~CowEvent() {
    
}

void CowEvent::update(const cv::Mat& image) {
    this->image = image;
    // cv::Size textTimeSize = cv::getTextSize(this->time, cv::FONT_HERSHEY_TRIPLEX, 2, 3, 0);

    // cv::putText(this->image, this->time, cv::Point(this->image.cols - textTimeSize.width - 30, 40 + textTimeSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 67, 255), 3);
    // Draw box
    for (auto box: this->boxes) {
        cv::rectangle(this->image, box, cv::Scalar(0, 255, 0), 4);
    }
    // CowProcessor* ip;
    // std::string ipcamera = ip->ipcamera;
    std::cout << "I'm Here = "  << std::endl; 
    if (!image.empty()){
    int a = this->boxes.size();
    std::string size = std::to_string(a);
    std::string nameImage = "../Event/" + this->ipcamera + "/personCow/" + this->time + "_" + std::to_string(this->frame) + "_size_" + size + ".jpg";
    // std::cout << "name Image = " <<nameImage << std::endl;
    cv::imwrite(nameImage, image);
    }
}
