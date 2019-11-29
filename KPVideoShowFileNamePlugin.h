//
// Created by karaler on 2019-10-29.
// Author: karaler
// Description:
// Others: 
// Copyright (c) 2019 ${ORGANIZATION_NAME}. All rights reserved.
//

#ifndef KPLAYER_KPVIDEOSHOWFILENAMEPLUGIN_H
#define KPLAYER_KPVIDEOSHOWFILENAMEPLUGIN_H

#include "adapter/KPPluginAdapter.h"
#include "util/KPHelper.h"

extern "C" {
#include <libavutil/error.h>
}

#include <utility>

extern KPEvent<std::string> global_event_play;

class KPVideoShowFileNamePlugin : public KPPluginAdapter {
protected:
    void Task() override;
    uint64_t     event_id       = -1;
    bool         show_extension = false;
    PluginParams params;
protected:
    int ChangeTitle(const std::string &);
public:
    explicit KPVideoShowFileNamePlugin(const std::string &identify_name, PluginParams params);
    ~KPVideoShowFileNamePlugin() override;
    void KillTask() override ;
    void InitTask() override ;
};


// slot
extern "C" {
__attribute__ ((visibility ("default"))) KPVideoShowFileNamePlugin *CreateInstance(PluginParams params);
}

#endif //KPLAYER_KPVIDEOSHOWFILENAMEPLUGIN_H
