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

extern KPEvent<std::string> global_event_play_updated;

class KPVideoShowFileNamePlugin : public KPPluginAdapter {
protected:
    std::string font_size      = "17";
    std::string font_color     = "white";
    std::string x              = "10";
    std::string y              = "10";
    uint64_t    event_id       = -1;
    std::string show_extension = "0";
protected:
    int ChangeTitle(const std::string &);
    void Task() override;
public:
    explicit KPVideoShowFileNamePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params_object);
    ~KPVideoShowFileNamePlugin() override;
    void KillTask() override;
    void InitTask() override;
};

// slot
extern "C" {
KPLAYER_PLUGIN_FUNC(KPVideoShowFileNamePlugin);
}

#endif //KPLAYER_KPVIDEOSHOWFILENAMEPLUGIN_H
