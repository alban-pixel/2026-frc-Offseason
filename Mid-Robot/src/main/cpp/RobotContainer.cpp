#include "RobotContainer.h"

#include <algorithm>
#include <frc/MathUtil.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  mCarDrive.SetDefaultCommand(mCarDrive.Run([this] {
    double throttle = mDriverController.GetRightTriggerAxis();
    double brake = mDriverController.GetLeftTriggerAxis();
    double steer = frc::ApplyDeadband(mDriverController.GetLeftX(), OperatorConstants::kJoystickDeadband);
    bool reverse = mDriverController.GetHID().GetBButton();
    bool drift = mDriverController.LeftBumper().Get();
    mCarDrive.drive(throttle, brake, steer, reverse, drift);
  }));

  mDriverController.A().WhileTrue(mCarDrive.getTestSteerCommand());
  mDriverController.X().WhileTrue(mCarDrive.Run([this] {
    double steerInput = 0.0;
    if (mLimelight.hasTarget()) {
      double steerScale = frc::SmartDashboard::GetNumber("Vision/SteerToTargetScale", 1.0);
      steerInput = std::clamp(steerScale * mLimelight.getTX() / CarDriveConstants::kMaxSteerAngle.value(), -1.0, 1.0);
    }
    mCarDrive.drive(0.0, 0.0, steerInput);
  }));
  mDriverController.POVLeft().OnTrue(mCarDrive.getZeroFLCommand());
  mDriverController.POVRight().OnTrue(mCarDrive.getZeroFRCommand());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return frc2::cmd::None();
}
