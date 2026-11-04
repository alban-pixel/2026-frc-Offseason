#pragma once

#include <memory>
#include <networktables/DoubleTopic.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc2/command/SubsystemBase.h>

class SubLimelight : public frc2::SubsystemBase {
 public:
  SubLimelight();

  bool hasTarget() const;
  double getTX() const;
  double getTY() const;
  double getTA() const;
  int getTagID() const;

  void Periodic() override;

 private:
  std::shared_ptr<nt::NetworkTable> mTable;

  nt::DoubleSubscriber mTVSub;
  nt::DoubleSubscriber mTXSub;
  nt::DoubleSubscriber mTYSub;
  nt::DoubleSubscriber mTASub;
  nt::DoubleSubscriber mTIDSub;

  bool mHasTarget{false};
  double mTX{0.0};
  double mTY{0.0};
  double mTA{0.0};
  int mTagID{-1};

  int mTelemetryCounter{0};
};
