/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_SENSORS_GPULIDARSENSOR_HH_
#define IGNITION_SENSORS_GPULIDARSENSOR_HH_

#include <memory>

#include <ignition/common/Event.hh>
#include <ignition/sensors/ign_sensors_gpu_lidar_export.hh>
#include <ignition/sensors/Sensor.hh>
#include <ignition/msgs.hh>

namespace ignition
{
  namespace sensors
  {
    /// \brief forward declarations
    class GpuLidarSensorPrivate;

    /// \brief GpuLidar Sensor Class
    ///
    ///   This class creates laser scans using the GPU. It's measures the range
    ///   from the origin of the center to points on the visual geometry in the
    ///   scene.
    ///
    ///   It offers both an ignition-transport interface and a direct C++ API
    ///   to access the image data. The API works by setting a callback to be
    ///   called with image data.
    class IGN_SENSORS_GPU_LIDAR_EXPORT GpuLidarSensor : public Sensor
    {
      /// \brief constructor
      public: GpuLidarSensor();

      /// \brief destructor
      public: virtual ~GpuLidarSensor();

      /// \brief Force the sensor to generate data
      /// \param[in] _now The current time
      /// \return true if the update was successfull
      public: virtual bool Update(const common::Time &_now) override;

      /// \brief Load the sensor with SDF parameters.
      /// \param[in] _sdf SDF Sensor parameters.
      /// \return true if loading was successful
      public: virtual bool Load(sdf::ElementPtr _sdf) override;

      /// \brief Initialize values in the sensor
      /// \return True on success
      public: virtual bool Init() override;

      /// \brief Set a callback to be called when data is generated.
      /// \param[in] _callback This callback will be called every time the
      /// sensor generates data. The Update function will be blocked while the
      /// callbacks are executed.
      /// \remark Do not block inside of the callback.
      /// \return A connection pointer that must remain in scope. When the
      /// connection pointer falls out of scope, the connection is broken.
      public: ignition::common::ConnectionPtr ConnectCallback(
                  std::function<
                  void (const ignition::msgs::LaserScan &)> _callback);

      /// \brief Data pointer for private data
      /// \internal
      private: std::unique_ptr<GpuLidarSensorPrivate> dataPtr;
    };
  }
}

#endif

