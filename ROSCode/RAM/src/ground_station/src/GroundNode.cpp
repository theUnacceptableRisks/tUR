//
// Created by korisd on 7/7/18.
//

#include "GroundNode.h"

GroundNode::GroundNode() : _node_handle("~")
{
    _node_handle.param( "refreshrate", _gtp_rate, 60 );
    _gtp_timer = _node_handle.createTimer( ros::Duration(_gtp_rate),boost::bind( &GroundNode::timerCallback, this, _1 ) );

    _serial_output = _node_handle.subscribe( "/serial_output", 10, &GroundNode::outputCallback, this );
    _command_subscriber = _node_handle.subscribe( "/command", 10, &GroundNode::commandCallback, this );
    _serial_input = _node_handle.advertise<std_msgs::UInt8MultiArray>( "/serial_input", 10 );

    _ambient = _node_handle.advertise<ground_station::Ambient> ("/ambient", 10 );
    _bbox = _node_handle.advertise<ground_station::BBox> ("/bbox", 10 );
    _arm_status = _node_handle.advertise<ground_station::ArmStatus> ("/arm_status", 10 );
    _arm_path = _node_handle.advertise<ground_station::PathLog> ( "/arm_path", 10 );

    std::chrono::system_clock::time_point chrono_now = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t( chrono_now );
    std::stringstream ss;
    ss << std::getenv( "HOME" ) << "/log_" << now  << ".txt";
    _log = ss.str();
}

void GroundNode::timerCallback( const ros::TimerEvent &event )
{
    std_msgs::UInt8MultiArray output;
    gtp spoof;

    snprintf( spoof.data, sizeof( spoof.data ), "%f,$GPGGA,202212.00,3024.7205,N,09110.7264,W,1,06,1.69,00061,M,-025,M,,*51,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,", ros::Time::now().toSec() );

    uint8_t *ptr = (uint8_t *)&spoof;
    for( int x = 0; x < sizeof( gtp ); x++ )
        output.data.push_back( *ptr++ );

    _serial_input.publish(output);
}

void GroundNode::commandCallback( const ram_network::HaspCommand::ConstPtr &msg )
{
    std_msgs::UInt8MultiArray output;
    ground_command com;
    com.command[0] = msg->com_id;
    com.command[1] = msg->com_param;

    auto *ptr = (uint8_t *)&com;
    for( int x = 0; x < sizeof( ground_command ); x++ )
        output.data.push_back( *ptr++ );

    _serial_input.publish(output);

}

void GroundNode::outputCallback( const std_msgs::UInt8MultiArray::ConstPtr &msg )
{
    /* Grab Data and Write to File */
    std::ofstream output_file;
    output_file.open( _log, std::ofstream::app );
    for( auto val : msg->data )
    {
        _buffer.push_back( val );
        output_file <<  val;
    }
    output_file.close();

    if( _buffer.size() == sizeof( data_packet ) )
    {
        data_packet data;
        auto *ptr = (uint8_t *)&data;
        for( auto val : _buffer )
        {
            *ptr++ = val;
        }
        if( data.verifyCheckSums() )
        {
            ROS_ERROR( "Check Sums Validated!" );
            uint16_t offset = 0;
            for( int x = 0; x < data.num_data_chunks; x++ )
            {
                switch( data.meat[offset] )
                {
                    case '\x31':
                    {
                        //ambient
                        ambient_packet packet = extractPacket<ambient_packet>( data, offset );
                        publishAmbient( packet );
                        break;
                    }
                    case '\x32':
                    {
                        //bbox
                        bbox_packet packet = extractPacket<bbox_packet>( data, offset );
                        publishBBox( packet );
                        break;
                    }
                    case '\x33':
                    {
                        //arm_packet
                        arm_packet packet = extractPacket<arm_packet>( data, offset );
                        publishArmStatus( packet );
                        break;
                    }
                    case '\x35':
                    {
                        //pathlog
                        pathlog_packet packet = extractPacket<pathlog_packet>( data, offset );
                        publishPathLog( packet );
                        break;
                    }
                }
            }
        }
        else
        {
            ROS_ERROR( "Bad Checksums!" );
        }
        ROS_ERROR( "Clearing Buffer" );
        _buffer.clear();

    }
    else if( _buffer.size() > sizeof( data_packet ) )
    {
        _buffer.clear();
        ROS_ERROR( "There's been buffer overflow!!!" );
    }

}

template<typename packet_type>
packet_type GroundNode::extractPacket( data_packet &data, uint16_t &offset )
{
    packet_type packet;
    memcpy( &packet, &data.meat[offset], sizeof( packet_type ) );
    offset += sizeof( packet_type );
    return packet;
}

void GroundNode::publishAmbient( ambient_packet &packet )
{
    ground_station::Ambient msg;

    msg.time_recorded = packet.time_recorded;

    msg.bme01_temp = packet.bme01_temp;
    msg.bme01_pres = packet.bme01_pres;
    msg.bme01_humi = packet.bme01_humi;

    msg.bme02_temp = packet.bme02_temp;
    msg.bme02_pres = packet.bme02_pres;
    msg.bme02_humi = packet.bme02_humi;

    msg.dallas01_temp = packet.dallas01_temp;
    msg.dallas02_temp = packet.dallas01_temp;
    msg.dallas03_temp = packet.dallas01_temp;
    msg.dallas04_temp = packet.dallas01_temp;
    msg.dallas05_temp = packet.dallas01_temp;
    msg.dallas06_temp = packet.dallas01_temp;
    msg.dallas07_temp = packet.dallas01_temp;
    msg.dallas08_temp = packet.dallas01_temp;
    msg.dallas09_temp = packet.dallas01_temp;
    msg.dallas10_temp = packet.dallas01_temp;
    msg.dallas11_temp = packet.dallas01_temp;
    msg.dallas12_temp = packet.dallas01_temp;
    msg.dallas13_temp = packet.dallas01_temp;
    msg.dallas14_temp = packet.dallas01_temp;
    msg.dallas15_temp = packet.dallas01_temp;
    msg.dallas16_temp = packet.dallas01_temp;

    _ambient.publish(msg);
}

void GroundNode::publishBBox( bbox_packet &packet )
{
    ground_station::BBox msg;

    msg.time_recorded = packet.time_recorded;

    msg.rocker_horiz = packet.rocker_horiz;
    msg.rocker_verti = packet.rocker_verti;
    msg.toggle_horiz = packet.toggle_horiz;
    msg.toggle_verti = packet.toggle_verti;

    msg.button_blu = packet.button_blu;
    msg.potentiometer_lever = packet.potentiometer_lever;
    msg.potentiometer_knob = packet.potentiometer_knob;

    _bbox.publish(msg);
}

void GroundNode::publishArmStatus( arm_packet &packet )
{
    ground_station::ArmStatus msg;

}

void GroundNode::publishPathLog( pathlog_packet &packet )
{
    ground_station::PathLog msg;
}