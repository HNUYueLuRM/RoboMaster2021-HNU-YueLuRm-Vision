#include "../TaskSwitcher/TaskSwitcher.h"

namespace hnurm
{

TaskSwitcher::TaskSwitcher()
    : _Armor_tracker(make_unique<Armor_tracker>()),
        _Angle_solver(make_unique<AngleSolver>()),
        _Armor_Detector(make_unique<ArmorDetector>())
    {

    }

void TaskSwitcher::RunSwitcher(Wrapped<SolveEssential> &tmp_se, Wrapped<ImageData> &raw_image, Wrapped<SerialData> &solved_data)
{
    cv::Mat current_frame = raw_image.raw_data.mat;
    cv::Rect target_rect;

    switch(tmp_se.raw_data.work_mode)
    {
        case Protocol::Work_mode::manual:
            std::cout << "Work mode : Manual" << std::endl;
            return;
        case Protocol::Work_mode::auto_shoot:
            std::cout << "Work mode : Auto Shoot" << std::endl;
            break;
        default:
            std::cout << "Unknown mode" << std::endl;
            break;
    }

    if(tmp_se.raw_data.work_mode==Protocol::Work_mode::auto_shoot)
    {
        if(!_Armor_Detector->Detect(current_frame, target_rect))
        {
            cv::imshow("TestWindow", current_frame);
            cv::waitKey(1);
            std::cout << "No Armor" << std::endl;
            lost_count++;
        }
        else
        {
            lost_count=0;
            rectangle(current_frame, target_rect, Scalar(0,255,255), 2);
            imshow("TestWindow",current_frame);
            waitKey(1);
        }

        float speed;
        switch (tmp_se.raw_data.bullet_speed)
        {
            case Protocol::Bullet_speed::hero10:
                speed = 10.0;break;
            case Protocol::Bullet_speed::hero16:
                speed = 16.0;break;
            case Protocol::Bullet_speed::infantry15:
                speed = 15.0;break;
            case Protocol::Bullet_speed::infantry18:
                speed = 18.0;break;
            case Protocol::Bullet_speed::infantry30:
                speed = 30.0;break;
            default:
                speed = 0;break;
        }
    }

    if(tmp_se.raw_data.work_mode==Protocol::Work_mode::auto_windmill)
    {
        
    }

//below are solve part

    if(!lost_count)
    {
        solved_data.raw_data = _Angle_solver->Solve_Angle(tmp_se.raw_data.abs_angle, 20.0, target_rect);
        solved_data.raw_data.camera_id = raw_image.raw_data.camera_id;
        makeshift_data=solved_data.raw_data;
    }
    else
    {
        GetPatchData();
        solved_data=makeshift_data;
    }
    
}
    


void TaskSwitcher::SetEnemyColor(Protocol::Self_color mycolor)
{
    if(mycolor==Protocol::Self_color::red)
    {
        _Armor_Detector->set_color(0);
    }
    else
    {
        _Armor_Detector->set_color(1);
    }
}



void TaskSwitcher::GetPatchData()
{
    if(lost_count>6)
    {
        makeshift_data=SerialData(0,0,0,0);
    }
    else
    {
        makeshift_data.pitch=(MAX_LOST_COUNT-lost_count+1)/MAX_LOST_COUNT*makeshift_data.pitch;
        makeshift_data.yaw=(MAX_LOST_COUNT-lost_count+1)/MAX_LOST_COUNT*makeshift_data.yaw;
    }
}

}//hnurm
