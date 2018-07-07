//
// Created by korisd on 7/7/18.
//

#include "cam_monitor/CamMonitor.h"

CamMonitor::CamMonitor() : _node_handle("~")
{
    _node_handle.param( "img_topic", _img_topic, std::string( "/usb_cam_one/image_raw" ) );
    _node_handle.param( "video_location", _video_location, std::string( "" ) );
    _node_handle.param( "snap_location", _snap_location, std::string( "" ) );
    _image_sub  = _node_handle.subscribe( _img_topic, 10, &CamMonitor::imageCallback, this );
    _time_sub   = _node_handle.subscribe( "/clock", 10, &CamMonitor::timeCallback, this );
    _take_snap  = _node_handle.advertiseService( ( ros::this_node::getName() + "/takeSnap" ), &CamMonitor::serviceCallback, this );
}

void CamMonitor::timeCallback( const rosgraph_msgs::Clock::ConstPtr &msg )
{
    _clock = *msg;
}

void CamMonitor::imageCallback( const sensor_msgs::Image::ConstPtr &msg )
{
    _recent_img = cv_bridge::toCvCopy( msg, sensor_msgs::image_encodings::BGR8 );

    if( !boost::filesystem::exists( _video_location) )
        boost::filesystem::create_directories( _video_location );

    std::stringstream img_name;
    img_name << _video_location << _clock.clock.toSec() << ".jpg";

    cv::imwrite( img_name.str(), _recent_img->image );
}

bool CamMonitor::serviceCallback( cam_monitor::SnapRequest &request, cam_monitor::SnapResponse &response )
{
    if( !boost::filesystem::exists( _snap_location ) )
        boost::filesystem::create_directories( _snap_location );

    cv::imwrite( ( _snap_location + "snap.jpg" ), _recent_img->image );
    response.done = true;
    return true;
}