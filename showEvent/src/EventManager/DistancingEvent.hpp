//
//  DistancingEvent.hpp
//  CamHub
//
//  Created by Nguyen Xuan Truong on 29/07/2020.
//  Copyright © 2020 Nguyen Xuan Truong. All rights reserved.
//

#ifndef DistancingEvent_hpp
#define DistancingEvent_hpp

#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class DistancingEvent {
public:
    DistancingEvent(int cameraId, const std::vector<cv::Rect>& boxes, const std::vector<std::vector<float>>& distances,const std::string& time, const std::string& date, std::string frame);
    ~DistancingEvent();
    
    void update(const cv::Mat& image);
    
    int cameraId;
    std::vector<cv::Rect> boxes;
    std::vector<std::vector<float>> distances;
    std::string time;
    std::string date;
    std::string frame;
    cv::Mat image;
};

#endif /* DistancingEvent_hpp */