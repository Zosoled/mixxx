#ifndef SOUNDDEVICENETWORK_H
#define SOUNDDEVICENETWORK_H

#include <QString>

#include "soundio/sounddevice.h"

#define CPU_USAGE_UPDATE_RATE 30 // in 1/s, fits to display frame rate
#define CPU_OVERLOAD_DURATION 500 // in ms

class SoundManager;
class EngineNetworkStream;

class SoundDeviceNetwork : public SoundDevice {
  public:
    SoundDeviceNetwork(UserSettingsPointer config,
                       SoundManager *sm,
                       const std::unique_ptr<EngineNetworkStream>& pNetworkStream);
    virtual ~SoundDeviceNetwork();

    virtual SoundDeviceError open(bool isClkRefDevice, int syncBuffers);
    virtual bool isOpen() const;
    virtual SoundDeviceError close();
    virtual void readProcess();
    virtual void writeProcess();
    virtual QString getError() const;

    virtual unsigned int getDefaultSampleRate() const {
        return 44100;
    }

  private:
    const std::unique_ptr<EngineNetworkStream>& m_pNetworkStream;
    FIFO<CSAMPLE>* m_outputFifo;
    FIFO<CSAMPLE>* m_inputFifo;
    bool m_outputDrift;
    bool m_inputDrift;
    static volatile int m_underflowHappened;
};

#endif // SOUNDDEVICENETWORK_H
