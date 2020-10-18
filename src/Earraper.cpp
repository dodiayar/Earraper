#define MINIAUDIO_IMPLEMENTATION
#include <iostream>
#include <memory>
#include <flags.h>
#include <miniaudio.h>
#include <rang.hpp>

bool boosted = false;
int boostLevel;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    MA_ASSERT(pDevice->capture.format == pDevice->playback.format);
    MA_ASSERT(pDevice->capture.channels == pDevice->playback.channels);
    /* In this example the format and channel count are the same for both input and output which means we can just memcpy(). */
    float* outputBuffer = static_cast<float*>(pOutput);
    const float* firstFrame = static_cast<const float*>(pInput);
    for (int i = 0; i < frameCount * 2; i++) {
        float value = *(firstFrame + i);
        if (boosted) value *= boostLevel;
        memcpy(outputBuffer + i, &value, sizeof(float));
    }
}

int main(int argc, char** argv) {
    const flags::args args(argc, argv);
    const auto playbackDeviceId = args.get<int>("playback"),
        recordingDeviceId = args.get<int>("recording"),
        oBoostLevel = args.get<int>("boost");
    boostLevel = oBoostLevel ? *oBoostLevel : 50;
    ma_context context;
    ma_context_init(NULL, 0, NULL, &context);
    ma_device_config deviceConfig;
    ma_device device;
    ma_device_info* pPlaybackInfos;
    ma_uint32 playbackCount;
    ma_device_info* pCaptureInfos;
    ma_uint32 captureCount;
    ma_context_get_devices(&context, &pPlaybackInfos, &playbackCount, &pCaptureInfos, &captureCount);

    deviceConfig = ma_device_config_init(ma_device_type_duplex);
    deviceConfig.capture.pDeviceID = recordingDeviceId ? &pCaptureInfos[*recordingDeviceId].id : NULL;
    deviceConfig.capture.format = ma_format_f32;
    deviceConfig.capture.channels = 2;
    deviceConfig.capture.shareMode = ma_share_mode_shared;
    deviceConfig.playback.pDeviceID = playbackDeviceId ? &pPlaybackInfos[*playbackDeviceId].id : NULL;
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.dataCallback = data_callback;
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
        return -1;

    ma_device_start(&device);

    for (;;) {
        if (boosted) std::cout << rang::style::bold << rang::fg::green << "Boosted" << std::endl;
        else std::cout << rang::style::bold << rang::fg::red << "Not Boosted" << std::endl;
        std::cout << rang::style::reset << rang::fg::yellow << "Press Enter to boost!";
        getchar();
        boosted = !boosted;
        system("cls");
    }

    ma_device_uninit(&device);

    return 0;
}
