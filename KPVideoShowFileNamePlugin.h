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

#include "config.h"

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
    explicit KPVideoShowFileNamePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParams params);
    ~KPVideoShowFileNamePlugin() override;
    void KillTask() override;
    void InitTask() override;
};

// slot
extern "C" {
KPLAYER_PLUGIN_FUNC(KPVideoShowFileNamePlugin);
}

#endif //KPLAYER_KPVIDEOSHOWFILENAMEPLUGIN_H
