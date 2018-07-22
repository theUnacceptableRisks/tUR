//
// Created by korisd on 5/29/18.
//

#include "arm_motion/ArmTrial.h"

ArmTrial::ArmTrial( arm_motion::ServoChange sc, geometry_msgs::Pose &pose, bool *success ) : _servo_based_fk_pose(pose), _active(false),
                                                                               _complete(false), _on_motion(),
                                                                               _action_client( _node_handle, "arm_motion_driver", true ),
                                                                               _servo_client( _node_handle, "arm_motion_driver_servo", true )
{
    arm_motion::MotionMsg motion;
    motion.velocity = 5;
    motion.type = SERVO_R;
    switch( sc.servo_id )
    {
        case 0:
            motion.servo_one = sc.servo_change;
            break;
        case 1:
            motion.servo_two = sc.servo_change;
            break;
        case 2:
            motion.servo_three = sc.servo_change;
            break;
        case 3:
            motion.servo_four = sc.servo_change;
            break;
        case 4:
            motion.servo_five = sc.servo_change;
            break;
        case 5:
            motion.servo_six = sc.servo_change;
            break;
    }
    _motions.push_back( motion );
    _trial_name = "manual_servo";
    *success = _servo_client.waitForServer( ros::Duration( 10 ) );
}

ArmTrial::ArmTrial( arm_motion::ManualWaypoint wp, geometry_msgs::Pose &pose, bool *success ) : _servo_based_fk_pose(pose), _active(false),
                                                                                  _complete(false), _on_motion(),
                                                                                  _action_client( _node_handle, "arm_motion_driver", true ),
                                                                                  _servo_client( _node_handle, "arm_motion_driver_servo", true )

{
    arm_motion::MotionMsg motion;
    motion.type = DISCRETE_W;
    motion.x = wp.x;
    motion.y = wp.y;
    motion.z = wp.z;
    motion.eeo = wp.eeo;
    motion.velocity = 5;
    motion.precision = 1;
    motion.smoothness = 2;
    motion.tolerance = 2;
    _motions.push_back( motion );
    _trial_name = "manual_waypoint";
    *success = _action_client.waitForServer( ros::Duration( 10 ) );
}

ArmTrial::ArmTrial( std::string trial_name, lua_State *lua, geometry_msgs::Pose &pose, bool *success ) : _servo_based_fk_pose(pose),_trial_name(trial_name),
                                                                              _active(false), _complete(false),
                                                                              _on_motion(), _action_client( _node_handle, "arm_motion_driver", true ),
                                                                              _servo_client( _node_handle, "arm_motion_driver_servo", true )

{
    std::stringstream ss;
    ss << std::getenv( ram_scripts ) << trial_name << ".lua";

    if( luaL_loadfile( lua, ss.str().c_str() ) || lua_pcall( lua, 0, 1, 0 ) )
    {
        ROS_ERROR( "%s: %s", __FUNCTION__, lua_tostring( lua, -1 ) );
        *success = false;
    }
    else
    {
        /* factor to function */
        lua_len( lua, -1 );
        auto size = (int)lua_tointeger( lua, -1 );
        lua_pop( lua, 1 );


        for( int i = 1; i < size+1; i++ )
        {
            arm_motion::MotionMsg motion;
            /* stack: trial table */
            /* get the motion at i */
            lua_pushinteger( lua, i );
            lua_gettable( lua, -2 );

            /*
             * TODO: check for nils!!!
             * TODO: FACTOR
             */
            /*
             * Velocity
             */
            /* stack: trial table -> motion[i] */
            lua_pushstring( lua, "velocity" );
            /* stack: trial table -> motion[i] -> "velocity" */
            lua_gettable( lua, -2 );
            /* stack: trial table -> motion[i] -> velocity num */
            motion.velocity = (uint8_t)lua_tointeger( lua, -1 );
            lua_pop( lua, 1 );
            /* stack: trial table -> motion[i] */

            /*
             * Type
             */
            lua_pushstring( lua, "type" );
            lua_gettable( lua, -2 );
            motion.type = (uint8_t)lua_tointeger( lua, -1 );
            lua_pop( lua, 1 );

            /*
             * Precision
             */
            lua_pushstring( lua, "precision" );
            lua_gettable( lua, -2 );
            motion.precision = (uint8_t)lua_tointeger( lua, -1 );
            lua_pop( lua, 1 );

            /*
             * Smoothness
             */
            lua_pushstring( lua, "smoothness" );
            lua_gettable( lua, -2 );
            motion.smoothness = (uint16_t)lua_tointeger( lua, -1 );
            ROS_INFO( "Smoothness[%d]", (int)motion.smoothness );
            lua_pop( lua, 1 );

            /*
             * Tolerance
             */
            lua_pushstring( lua, "tolerance" );
            lua_gettable( lua, -2 );
            motion.tolerance = (uint16_t)lua_tointeger( lua, - 1 );
            lua_pop( lua, 1 );

            /*
             * Shape
             */
            lua_pushstring( lua, "shape" );
            lua_gettable( lua, -2 );
            motion.shape = std::string( lua_tostring( lua, -1 ) );
            lua_pop( lua, 1 );

            /*
             * EEO
             */
            lua_pushstring( lua, "eeo" );
            lua_gettable( lua, -2 );
            motion.eeo = lua_tonumber( lua, -1 );
            lua_pop( lua, 1 );

            /*
             * X
             */
            lua_pushstring( lua, "x" );
            lua_gettable( lua, -2 );
            motion.x = lua_tonumber( lua, -1 );
            lua_pop( lua, 1 );

            /*
             * Y
             */
            lua_pushstring( lua, "y" );
            lua_gettable( lua, -2 );
            motion.y = lua_tonumber( lua, -1 );
            lua_pop( lua, 1 );

            /*
             * Z
             */
            lua_pushstring( lua, "z" );
            lua_gettable( lua, -2 );
            motion.z = lua_tonumber( lua, -1 );
            lua_pop( lua, 2 ); /* pop the number and the motion off */
            /* stack: trial table */
            _motions.push_back( motion );
        }
        lua_pop( lua, 1 );
        /* stack: nil */
        setupServiceClient();
        *success = _action_client.waitForServer( ros::Duration( 10 ) );
    }
}

void ArmTrial::setupServiceClient()
{
    _path_service = _node_handle.serviceClient<arm_motion::PathService>("plan_a_path");
}

void ArmTrial::servoBasedFK( const geometry_msgs::Pose::ConstPtr &pose )
{
    _servo_based_fk_pose = *pose;
}

bool ArmTrial::isActive()
{
    return _active;
}

bool ArmTrial::isComplete()
{
    return _complete;
}

bool ArmTrial::start( int start_time )
{
    bool success = true;
    if( !_complete )
    {
        _start_time = start_time;
        generateMotion();
        _active = true;
    }
    else
    {
        ROS_ERROR( "%s: %s attempting to start an already completed trial", __FUNCTION__, _trial_name.c_str() );
        success = false;
    }
    return success;
}

void ArmTrial::generateMotion()
{
    arm_motion::PathService srv;

    srv.request.motion = _motions[_on_motion];
    srv.request.present_position = _servo_based_fk_pose;
    if( srv.request.motion.type == SERVO_R || srv.request.motion.type == SERVO_ABSOLUTE )
    {
        arm_motion::ServoMotionGoal servo_goal;
        servo_goal.type = _motions[_on_motion].type;
        servo_goal.velocity = _motions[_on_motion].velocity;
        servo_goal.servo_one = _motions[_on_motion].servo_one;
        servo_goal.servo_two = _motions[_on_motion].servo_two;
        servo_goal.servo_three = _motions[_on_motion].servo_three;
        servo_goal.servo_four = _motions[_on_motion].servo_four;
        servo_goal.servo_five = _motions[_on_motion].servo_five;
        servo_goal.servo_six = _motions[_on_motion].servo_six;

        _servo_client.sendGoal( servo_goal,
                                boost::bind( &ArmTrial::servoCompleteCallback, this, _1, _2 ),
                                actionlib::SimpleActionClient<arm_motion::ServoMotionAction>::SimpleActiveCallback(),
                                actionlib::SimpleActionClient<arm_motion::ServoMotionAction>::SimpleFeedbackCallback());

    }
    else
    {
        if( _path_service.call( srv ))
        {
            arm_motion::ArmMotionGoal action_goal;
            action_goal.joints = srv.response.joints;
            for( const auto &joint : action_goal.joints )
            {
                std::cout << joint << std::endl;
            }

            _action_client.sendGoal( action_goal,
                                     boost::bind( &ArmTrial::motionCompleteCallback, this, _1, _2 ),
                                     actionlib::SimpleActionClient<arm_motion::ArmMotionAction>::SimpleActiveCallback(),
                                     actionlib::SimpleActionClient<arm_motion::ArmMotionAction>::SimpleFeedbackCallback());
            //TODO: figure out how to bind the feedback    boost::bind( &ArmTrial::motionFeedbackCallback, this, _1 ) );

        }
        else
        {
            ROS_ERROR( "%s: cannot perform motion", __FUNCTION__ );
        }
    }
}

void ArmTrial::motionCompleteCallback( const actionlib::SimpleClientGoalState &state,
                                       const arm_motion::ArmMotionResultConstPtr &result )
{
    if( result->success )
    {
        _on_motion++;
        if( _on_motion >= _motions.size() )
        {
            _complete = true;
        }
        else
        {
            generateMotion();
        }
    }
    else
    {
        ROS_ERROR( "%s: reporting that Motion has failed.", __FUNCTION__ );
        _complete = true;
    }
}

void ArmTrial::motionFeedbackCallback( const arm_motion::ArmMotionActionFeedbackConstPtr &feedback )
{

}

void ArmTrial::servoCompleteCallback( const actionlib::SimpleClientGoalState &state,
                                      const arm_motion::ServoMotionResultConstPtr &result )
{
    if( result->success )
    {
        _on_motion++;
        if( _on_motion >= _motions.size() )
        {
            _complete = true;
        }
        else
        {
            generateMotion();
        }
    }
    else
    {
        ROS_ERROR( "%s: reporting that Motion has failed.", __FUNCTION__ );
        _complete = true;
    }
}

void ArmTrial::servoFeedbackCallback( const arm_motion::ServoMotionActionFeedbackConstPtr &feedback )
{

}