//
// Created by korisd on 7/5/18.
//

#include <ram_network/ram_network.h>
#include "ram_network/NetworkNode.h"

NetworkNode::NetworkNode()
{
    setupSerialConnection();
    setupI2CConnections();
    setupServices();
    setupTimers();
}

void NetworkNode::setupSerialConnection()
{
    int attempts = 0;
    while( _handles.serial == -1 )
    {
        _handles.serial = serialOpen( serialAddress, serialBaud );
        if( _handles.serial != -1 )
        {
            ROS_INFO( "%s: Serial successfully connected" );
        }
        else if( attempts++ > serialLimit )
        {
            ROS_ERROR( "%s: Serial failed to connect", __FUNCTION__ );
            break;
        }
    }
}

void NetworkNode::setupI2CConnections()
{
    openAdaI2C();
    openBBoxI2C();
}

void NetworkNode::setupTimers()
{
    _network_loop = _node_handle.createTimer( ros::Duration( refreshRate ), boost::bind( &NetworkNode::networkLoop, this, _1 ) );
}

void NetworkNode::openAdaI2C()
{
    _handles.ada = wiringPiI2CSetup( I2CADDRESS_ADA );
}

void NetworkNode::openBBoxI2C()
{
    _handles.bbox = wiringPiI2CSetup( I2CADDRESS_BBOX );
}

void NetworkNode::networkLoop()
{
    if( _handles.serial != -1 )
    {
        // TODO below
        // check for incoming
        // parse incoming
        // handle commands
        // handle gps
          // set ada input register new_sync true
          // update register gps sync
    }
    else
    {
        ROS_ERROR( "%s: we are in pure autonomous mode, attempting to reestablish connection", __FUNCTION__ );
        setupSerialConnection();
    }
    if( _handles.ada != -1 )
    {
        /*
         * Write Time
         */
        if( _registers.ada_output_register.write_fault )
        {
            _registers.ada_input_register.last_write    = _registers.ard_time_sync;
            _registers.ada_input_register.has_command   = 0;
            _registers.ada_input_register.command_id    = 0;
            _registers.ada_input_register.command_param = 0;
            if( !_ada_commands.empty() )
            {
                //TODO handle commading
                //TODO if command fault is set, don't send any commands (let that be cleared by ground)
            }
            else
            {
                _registers.ada_input_register.has_command   = 0;
            }
        }
        // write either new write or the same thing if there was a fault on the previous
        _registers.ada_input_register.setCheckSums();
        write( _handles.ada, (byte *)&_registers.ada_input_register, sizeof( ADA_input_register ) );
        // TODO bad write checking?
        // read

        ADA_output_register new_read;
        read( _handles.ada, (byte *)&new_read, sizeof( ADA_output_register ) );
        // TODO verify read?

        // check sums ( if bad, toss the whole read )
        //            ( if good, check for faults + update register )
        // check write fault (if write fault but checksum good, read data)
          // if not write fault, set new sync to 0
        // command faults will be handled by global reporting, TODO how do we clear?
        // update register


        if( new_read.verifyCheckSums() )
        {
            if( !new_read.write_fault )
                _registers.ada_input_register.new_sync = 0;
            _registers.ada_output_register = new_read;
        }
        else
        {
            // TODO report fault somewhere
        }
    }
    else
    {
        /*
         * Attempt to open connection with ADA
         */
        openAdaI2C();
    }

    if( _handles.bbox != -1 )
    {
        _registers.bbox_input_register.sync_to = _registers.ard_time_sync;
    }
    else
    {
        /*
         * Attempt to open connection with BBox
         */
        openBBoxI2C();
    }

    if( _handles.serial != -1 )
    {
        //downlinking
        downlinkPacket();
    }

}