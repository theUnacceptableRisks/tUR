//
// Created by korisd on 7/7/18.
//

#ifndef GROUNDNODE_H
#define GROUNDNODE_H

#include <ground_node.h>
#include <fstream>
#include <chrono>

class GroundNode
{
    public:
        GroundNode();

    protected:
        std::string _log;
        ros::NodeHandle _node_handle;
        ros::Timer      _gtp_timer;
        int _gtp_rate;
        void timerCallback( const ros::TimerEvent &event );

        ros::Subscriber _command_subscriber;
        ros::Subscriber _serial_output;
        ros::Publisher _serial_input;
        void commandCallback( const ram_network::HaspCommand::ConstPtr &msg );
        void outputCallback( const std_msgs::ByteMultiArray::ConstPtr &msg );
        std::vector<uint8_t> _buffer;
};


#endif //HASP_GROUND_STATION_GROUNDNODE_H
