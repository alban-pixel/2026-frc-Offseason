#include "subsystems/SubLimelight.h"

#include <string>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"

SubLimelight::SubLimelight() {
  mTable = nt::NetworkTableInstance::GetDefault().GetTable(std::string{VisionConstants::kLimelightName});

  mTVSub = mTable->GetDoubleTopic("tv").Subscribe(0.0);
  mTXSub = mTable->GetDoubleTopic("tx").Subscribe(0.0);
  mTYSub = mTable->GetDoubleTopic("ty").Subscribe(0.0);
  mTASub = mTable->GetDoubleTopic("ta").Subscribe(0.0);
  mTIDSub = mTable->GetDoubleTopic("tid").Subscribe(-1.0);

  frc::SmartDashboard::SetDefaultNumber("Vision/SteerToTargetScale", 1.0);
}

bool SubLimelight::hasTarget() const {
  return mHasTarget;
}

double SubLimelight::getTX() const {
  return mTX;
}

double SubLimelight::getTY() const {
  return mTY;
}

double SubLimelight::getTA() const {
  return mTA;
}

int SubLimelight::getTagID() const {
  return mTagID;
}

void SubLimelight::Periodic() {
  mHasTarget = mTVSub.Get() >= 1.0;
  mTX = mTXSub.Get();
  mTY = mTYSub.Get();
  mTA = mTASub.Get();
  mTagID = static_cast<int>(mTIDSub.Get());

  mTelemetryCounter++;
  if (mTelemetryCounter < 5) {
    return;
  }
  mTelemetryCounter = 0;

  frc::SmartDashboard::PutBoolean("Limelight/HasTarget", mHasTarget);
  frc::SmartDashboard::PutNumber("Limelight/TXDeg", mTX);
  frc::SmartDashboard::PutNumber("Limelight/TYDeg", mTY);
  frc::SmartDashboard::PutNumber("Limelight/TAPercent", mTA);
  frc::SmartDashboard::PutNumber("Limelight/TagID", mTagID);
}
