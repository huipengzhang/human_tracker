//#line 2 "/opt/ros/fuerte/stacks/dynamic_reconfigure/templates/ConfigType.h"
// *********************************************************
// 
// File autogenerated for the aravis_camera_driver package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

/***********************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ***********************************************************/

// Author: Blaise Gassend


#ifndef __aravis_camera_driver__BASLERCAMERACONFIG_H__
#define __aravis_camera_driver__BASLERCAMERACONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace aravis_camera_driver
{
  class BaslerCameraConfigStatics;
  
  class BaslerCameraConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(BaslerCameraConfig &config, const BaslerCameraConfig &max, const BaslerCameraConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const BaslerCameraConfig &config1, const BaslerCameraConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, BaslerCameraConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const BaslerCameraConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, BaslerCameraConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const BaslerCameraConfig &config) const = 0;
      virtual void getValue(const BaslerCameraConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T BaslerCameraConfig::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (BaslerCameraConfig::* field);

      virtual void clamp(BaslerCameraConfig &config, const BaslerCameraConfig &max, const BaslerCameraConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const BaslerCameraConfig &config1, const BaslerCameraConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, BaslerCameraConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const BaslerCameraConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, BaslerCameraConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const BaslerCameraConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const BaslerCameraConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, BaslerCameraConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); i++)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string name, std::string type, int parent, int id, bool s, T PT::* f) : AbstractGroupDescription(name, type, parent, id, s), field(f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;
        
        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++) 
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }
      
      virtual void updateParams(boost::any &cfg, BaslerCameraConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++) 
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); i++)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<BaslerCameraConfig::AbstractGroupDescriptionConstPtr> groups;
    };
    
class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(BaslerCameraConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = params.begin(); i != params.end(); i++)
      {
        boost::any val;
        (*i)->getValue(config, val);

        if("capture_mode"==(*i)->name){capture_mode = boost::any_cast<std::string>(val);}
        if("trigger_source"==(*i)->name){trigger_source = boost::any_cast<std::string>(val);}
        if("trigger_activation"==(*i)->name){trigger_activation = boost::any_cast<std::string>(val);}
        if("frame_rate"==(*i)->name){frame_rate = boost::any_cast<int>(val);}
        if("exposure_auto"==(*i)->name){exposure_auto = boost::any_cast<std::string>(val);}
        if("exposure_time"==(*i)->name){exposure_time = boost::any_cast<int>(val);}
        if("gain_mode"==(*i)->name){gain_mode = boost::any_cast<std::string>(val);}
        if("gain"==(*i)->name){gain = boost::any_cast<int>(val);}
        if("auto_white_balance_once"==(*i)->name){auto_white_balance_once = boost::any_cast<bool>(val);}
        if("digital_shift"==(*i)->name){digital_shift = boost::any_cast<int>(val);}
      }
    }

    std::string capture_mode;
std::string trigger_source;
std::string trigger_activation;
int frame_rate;
std::string exposure_auto;
int exposure_time;
std::string gain_mode;
int gain;
bool auto_white_balance_once;
int digital_shift;

    bool state;
    std::string name;

    
}groups;



//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      std::string capture_mode;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      std::string trigger_source;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      std::string trigger_activation;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      int frame_rate;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      std::string exposure_auto;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      int exposure_time;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      std::string gain_mode;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      int gain;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      bool auto_white_balance_once;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      int digital_shift;
//#line 255 "/opt/ros/fuerte/stacks/dynamic_reconfigure/templates/ConfigType.h"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("BaslerCameraConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }
    
    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const BaslerCameraConfig &__max__ = __getMax__();
      const BaslerCameraConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const BaslerCameraConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); i++)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const BaslerCameraConfig &__getDefault__();
    static const BaslerCameraConfig &__getMax__();
    static const BaslerCameraConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();
    
  private:
    static const BaslerCameraConfigStatics *__get_statics__();
  };
  
  template <> // Max and min are ignored for strings.
  inline void BaslerCameraConfig::ParamDescription<std::string>::clamp(BaslerCameraConfig &config, const BaslerCameraConfig &max, const BaslerCameraConfig &min) const
  {
    return;
  }

  class BaslerCameraConfigStatics
  {
    friend class BaslerCameraConfig;
    
    BaslerCameraConfigStatics()
    {
BaslerCameraConfig::GroupDescription<BaslerCameraConfig::DEFAULT, BaslerCameraConfig> Default("Default", "", 0, 0, true, &BaslerCameraConfig::groups);
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.capture_mode = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.capture_mode = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.capture_mode = "continuous";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("capture_mode", "str", 0, "Capture mode", "{'enum_description': 'Enum to set the capture mode.', 'enum': [{'srcline': 12, 'description': 'Continuous', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'continuous', 'ctype': 'std::string', 'type': 'str', 'name': 'Continuous'}, {'srcline': 13, 'description': 'Triggered', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'triggered', 'ctype': 'std::string', 'type': 'str', 'name': 'Triggered'}]}", &BaslerCameraConfig::capture_mode)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("capture_mode", "str", 0, "Capture mode", "{'enum_description': 'Enum to set the capture mode.', 'enum': [{'srcline': 12, 'description': 'Continuous', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'continuous', 'ctype': 'std::string', 'type': 'str', 'name': 'Continuous'}, {'srcline': 13, 'description': 'Triggered', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'triggered', 'ctype': 'std::string', 'type': 'str', 'name': 'Triggered'}]}", &BaslerCameraConfig::capture_mode)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.trigger_source = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.trigger_source = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.trigger_source = "Line1";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("trigger_source", "str", 0, "Trigger source", "{'enum_description': 'Enum to set the trigger source.', 'enum': [{'srcline': 16, 'description': 'Line 1', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'Line1', 'ctype': 'std::string', 'type': 'str', 'name': 'Line1'}, {'srcline': 17, 'description': 'Line 2', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'Line2', 'ctype': 'std::string', 'type': 'str', 'name': 'Line2'}]}", &BaslerCameraConfig::trigger_source)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("trigger_source", "str", 0, "Trigger source", "{'enum_description': 'Enum to set the trigger source.', 'enum': [{'srcline': 16, 'description': 'Line 1', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'Line1', 'ctype': 'std::string', 'type': 'str', 'name': 'Line1'}, {'srcline': 17, 'description': 'Line 2', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'Line2', 'ctype': 'std::string', 'type': 'str', 'name': 'Line2'}]}", &BaslerCameraConfig::trigger_source)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.trigger_activation = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.trigger_activation = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.trigger_activation = "RisingEdge";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("trigger_activation", "str", 0, "Trigger activation", "{'enum_description': 'Enum to set the trigger activation.', 'enum': [{'srcline': 20, 'description': 'Rising edge', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'RisingEdge', 'ctype': 'std::string', 'type': 'str', 'name': 'RisingEdge'}, {'srcline': 21, 'description': 'Falling edge', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'FallingEdge', 'ctype': 'std::string', 'type': 'str', 'name': 'FallingEdge'}]}", &BaslerCameraConfig::trigger_activation)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("trigger_activation", "str", 0, "Trigger activation", "{'enum_description': 'Enum to set the trigger activation.', 'enum': [{'srcline': 20, 'description': 'Rising edge', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'RisingEdge', 'ctype': 'std::string', 'type': 'str', 'name': 'RisingEdge'}, {'srcline': 21, 'description': 'Falling edge', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'FallingEdge', 'ctype': 'std::string', 'type': 'str', 'name': 'FallingEdge'}]}", &BaslerCameraConfig::trigger_activation)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.frame_rate = 1;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.frame_rate = 400;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.frame_rate = 30;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("frame_rate", "int", 0, "Frame rate", "", &BaslerCameraConfig::frame_rate)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("frame_rate", "int", 0, "Frame rate", "", &BaslerCameraConfig::frame_rate)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.exposure_auto = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.exposure_auto = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.exposure_auto = "auto";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("exposure_auto", "str", 0, "Exposure mode", "{'enum_description': 'Enum to set the exposure mode.', 'enum': [{'srcline': 25, 'description': 'Auto exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoExposure'}, {'srcline': 26, 'description': 'Auto once exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto_once', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoOnceExposure'}, {'srcline': 27, 'description': 'Fixed exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'fixed', 'ctype': 'std::string', 'type': 'str', 'name': 'FixedExposure'}]}", &BaslerCameraConfig::exposure_auto)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("exposure_auto", "str", 0, "Exposure mode", "{'enum_description': 'Enum to set the exposure mode.', 'enum': [{'srcline': 25, 'description': 'Auto exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoExposure'}, {'srcline': 26, 'description': 'Auto once exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto_once', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoOnceExposure'}, {'srcline': 27, 'description': 'Fixed exposure', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'fixed', 'ctype': 'std::string', 'type': 'str', 'name': 'FixedExposure'}]}", &BaslerCameraConfig::exposure_auto)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.exposure_time = 1;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.exposure_time = 65520;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.exposure_time = 1000;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("exposure_time", "int", 0, "Exposure (us)", "", &BaslerCameraConfig::exposure_time)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("exposure_time", "int", 0, "Exposure (us)", "", &BaslerCameraConfig::exposure_time)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.gain_mode = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.gain_mode = "";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.gain_mode = "auto";
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("gain_mode", "str", 0, "Gain mode", "{'enum_description': 'Enum to set the gain mode.', 'enum': [{'srcline': 30, 'description': 'Auto gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoGain'}, {'srcline': 31, 'description': 'Auto once gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto_once', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoOnceGain'}, {'srcline': 32, 'description': 'Fixed gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'fixed', 'ctype': 'std::string', 'type': 'str', 'name': 'FixedGain'}]}", &BaslerCameraConfig::gain_mode)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<std::string>("gain_mode", "str", 0, "Gain mode", "{'enum_description': 'Enum to set the gain mode.', 'enum': [{'srcline': 30, 'description': 'Auto gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoGain'}, {'srcline': 31, 'description': 'Auto once gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'auto_once', 'ctype': 'std::string', 'type': 'str', 'name': 'AutoOnceGain'}, {'srcline': 32, 'description': 'Fixed gain', 'srcfile': '../cfg/BaslerCamera.cfg', 'cconsttype': 'const char * const', 'value': 'fixed', 'ctype': 'std::string', 'type': 'str', 'name': 'FixedGain'}]}", &BaslerCameraConfig::gain_mode)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.gain = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.gain = 500;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.gain = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("gain", "int", 0, "Gain", "", &BaslerCameraConfig::gain)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("gain", "int", 0, "Gain", "", &BaslerCameraConfig::gain)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.auto_white_balance_once = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.auto_white_balance_once = 1;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.auto_white_balance_once = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<bool>("auto_white_balance_once", "bool", 0, "Auto white balance once", "", &BaslerCameraConfig::auto_white_balance_once)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<bool>("auto_white_balance_once", "bool", 0, "Auto white balance once", "", &BaslerCameraConfig::auto_white_balance_once)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __min__.digital_shift = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __max__.digital_shift = 4;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __default__.digital_shift = 0;
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.abstract_parameters.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("digital_shift", "int", 0, "Digital shift", "", &BaslerCameraConfig::digital_shift)));
//#line 259 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __param_descriptions__.push_back(BaslerCameraConfig::AbstractParamDescriptionConstPtr(new BaslerCameraConfig::ParamDescription<int>("digital_shift", "int", 0, "Digital shift", "", &BaslerCameraConfig::digital_shift)));
//#line 233 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      Default.convertParams();
//#line 233 "/opt/ros/fuerte/stacks/dynamic_reconfigure/src/dynamic_reconfigure/parameter_generator.py"
      __group_descriptions__.push_back(BaslerCameraConfig::AbstractGroupDescriptionConstPtr(new BaslerCameraConfig::GroupDescription<BaslerCameraConfig::DEFAULT, BaslerCameraConfig>(Default)));
//#line 390 "/opt/ros/fuerte/stacks/dynamic_reconfigure/templates/ConfigType.h"
    
      for (std::vector<BaslerCameraConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__); 
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__); 
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__); 
    }
    std::vector<BaslerCameraConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<BaslerCameraConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    BaslerCameraConfig __max__;
    BaslerCameraConfig __min__;
    BaslerCameraConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const BaslerCameraConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static BaslerCameraConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &BaslerCameraConfig::__getDescriptionMessage__() 
  {
    return __get_statics__()->__description_message__;
  }

  inline const BaslerCameraConfig &BaslerCameraConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }
  
  inline const BaslerCameraConfig &BaslerCameraConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }
  
  inline const BaslerCameraConfig &BaslerCameraConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }
  
  inline const std::vector<BaslerCameraConfig::AbstractParamDescriptionConstPtr> &BaslerCameraConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<BaslerCameraConfig::AbstractGroupDescriptionConstPtr> &BaslerCameraConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const BaslerCameraConfigStatics *BaslerCameraConfig::__get_statics__()
  {
    const static BaslerCameraConfigStatics *statics;
  
    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = BaslerCameraConfigStatics::get_instance();
    
    return statics;
  }

//#line 12 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_Continuous = "continuous";
//#line 13 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_Triggered = "triggered";
//#line 16 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_Line1 = "Line1";
//#line 17 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_Line2 = "Line2";
//#line 20 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_RisingEdge = "RisingEdge";
//#line 21 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_FallingEdge = "FallingEdge";
//#line 25 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_AutoExposure = "auto";
//#line 26 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_AutoOnceExposure = "auto_once";
//#line 27 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_FixedExposure = "fixed";
//#line 30 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_AutoGain = "auto";
//#line 31 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_AutoOnceGain = "auto_once";
//#line 32 "../cfg/BaslerCamera.cfg"
      const char * const BaslerCamera_FixedGain = "fixed";
}

#endif // __BASLERCAMERARECONFIGURATOR_H__