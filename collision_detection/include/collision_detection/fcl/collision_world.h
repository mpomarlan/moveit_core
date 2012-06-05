/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
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
 *********************************************************************/

/* Author: Ioan Sucan */

#ifndef COLLISION_DETECTION_FCL_COLLISION_WORLD_
#define COLLISION_DETECTION_FCL_COLLISION_WORLD_

#include "collision_detection/fcl/collision_robot.h"
#include <fcl/broad_phase_collision.h>

namespace collision_detection
{
  
  class CollisionWorldFCL : public CollisionWorld
  {
  public:
    
    CollisionWorldFCL(void);
    CollisionWorldFCL(const CollisionWorldFCL &other);
    virtual ~CollisionWorldFCL(void);
    
    virtual void checkRobotCollision(const CollisionRequest &req, CollisionResult &res, const CollisionRobot &robot, const planning_models::KinematicState &state) const;
    virtual void checkRobotCollision(const CollisionRequest &req, CollisionResult &res, const CollisionRobot &robot, const planning_models::KinematicState &state, const AllowedCollisionMatrix &acm) const;
    virtual void checkRobotCollision(const CollisionRequest &req, CollisionResult &res, const CollisionRobot &robot, const planning_models::KinematicState &state1, const planning_models::KinematicState &state2) const;
    virtual void checkRobotCollision(const CollisionRequest &req, CollisionResult &res, const CollisionRobot &robot, const planning_models::KinematicState &state1, const planning_models::KinematicState &state2, const AllowedCollisionMatrix &acm) const;
    virtual void checkWorldCollision(const CollisionRequest &req, CollisionResult &res, const CollisionWorld &other_world) const;
    virtual void checkWorldCollision(const CollisionRequest &req, CollisionResult &res, const CollisionWorld &other_world, const AllowedCollisionMatrix &acm) const;

    virtual double distanceRobot(const CollisionRobot &robot, const planning_models::KinematicState &state) const;  
    virtual double distanceRobot(const CollisionRobot &robot, const planning_models::KinematicState &state, const AllowedCollisionMatrix &acm) const;
    virtual double distanceWorld(const CollisionWorld &world) const;
    virtual double distanceWorld(const CollisionWorld &world, const AllowedCollisionMatrix &acm) const;
    
    virtual void addToObject(const std::string &id, const std::vector<shapes::ShapeConstPtr> &shapes, const std::vector<Eigen::Affine3d> &poses);
    virtual void addToObject(const std::string &id, const std::vector<shapes::StaticShapeConstPtr> &shapes);

    virtual void addToObject(const std::string &id, const shapes::StaticShapeConstPtr &shape);
    virtual void addToObject(const std::string &id, const shapes::ShapeConstPtr &shape, const Eigen::Affine3d &pose);
    virtual bool moveShapeInObject(const std::string &id, const shapes::ShapeConstPtr &shape, const Eigen::Affine3d &pose);
    virtual bool removeShapeFromObject(const std::string &id, const shapes::ShapeConstPtr &shape);
    virtual bool removeStaticShapeFromObject(const std::string &id, const shapes::StaticShapeConstPtr &shape);
    virtual void removeObject(const std::string &id);
    virtual void clearObjects(void);
    
  protected:

    void checkWorldCollisionHelper(const CollisionRequest &req, CollisionResult &res, const CollisionWorld &other_world, const AllowedCollisionMatrix *acm) const;
    void checkRobotCollisionHelper(const CollisionRequest &req, CollisionResult &res, const CollisionRobot &robot, const planning_models::KinematicState &state, const AllowedCollisionMatrix *acm) const;
    double distanceRobotHelper(const CollisionRobot &robot, const planning_models::KinematicState &state, const AllowedCollisionMatrix *acm) const;
    double distanceWorldHelper(const CollisionWorld &world, const AllowedCollisionMatrix *acm) const;
    
    void constructFCLObject(const Object *obj, FCLObject &fcl_obj) const;
    void updateFCLObject(const std::string &id);
    
    boost::scoped_ptr<fcl::BroadPhaseCollisionManager> manager_;
    std::map<std::string, FCLObject >                  fcl_objs_;
    
  };
  
}

#endif
