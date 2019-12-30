//
// Created by karaler on 2019-10-29.
// Author: karaler
// Description:
// Others: 
// Copyright (c) 2019 ${ORGANIZATION_NAME}. All rights reserved.
//

#include "KPVideoShowFileNamePlugin.h"

KPVideoShowFileNamePlugin::KPVideoShowFileNamePlugin(const std::string &identify_name, PluginParams params) : KPPluginAdapter(identify_name), params(params) {
    // 赋值信息
    filter_type = KP_FILTER_TYPE_VIDEO;
    filter_name = "video_plugin_show_file_name";

    // 赋值described
    std::stringstream filter_desc_stream;

    std::string font_size  = "17";
    std::string font_color = "white";
    if (params.find("font_size") != params.end()) {
        font_size = params["font_size"];
    }
    if (params.find("font_color") != params.end()) {
        font_color = params["font_color"];
    }

    filter_desc_stream << "x=10:y=10:fontfile=Res/font.ttf:fontsize=" << font_size << ":fontcolor=" << font_color << ":text='" << "[无]" << "'";
    filter_desc = filter_desc_stream.str();

    // 查找过滤器
    filter = avfilter_get_by_name("drawtext");
    if (filter == nullptr)
        throw KPFilterException("未知过滤器; filter name: drawtext");
}

KPVideoShowFileNamePlugin::~KPVideoShowFileNamePlugin() {
    global_event_play.Unsubscribe(event_id);
}

void KPVideoShowFileNamePlugin::Task() {
    // 初始化当前文件名
    auto current_title = global_event_play.GetLastVariable();
    logger->debug("获取到当前播放标题为: {}", current_title);
    ChangeTitle(current_title);


    // 监听下一次文件播放更改
    event_id = global_event_play.Subscribe([&](const std::string &file_path) {
        logger->debug("接收到事件通知，数据为：{}", file_path);
        ChangeTitle(file_path);
    });
}

void KPVideoShowFileNamePlugin::KillTask() {
}

void KPVideoShowFileNamePlugin::InitTask() {
    // 初始化当前文件名
    auto current_title = global_event_play.GetLastVariable();
    logger->debug("获取到当前播放标题为: {}", current_title);
    ChangeTitle(current_title);
}

int KPVideoShowFileNamePlugin::ChangeTitle(const std::string &file_path) {
    KPlayer::FileInfo file_info(file_path);
    std::string       title = show_extension ? file_info.GetFileName() : file_info.GetBaseFileName();

    AVDictionary *dict = nullptr;

    void *priv = GetFilterPriv();
    if (!priv) {
        logger->error("无法对plugin option进行设置; error: {}", "priv为空");
        return -1;
    }

    av_dict_set(& dict, "text", title.c_str(), 0);
    int ret = av_opt_set_dict(priv, & dict);
    if (ret < 0) {
        logger->error("无法对plugin option进行设置;");
        return ret;
    }
    return 0;
}

KPLAYER_PLUGIN_FUNC(KPVideoShowFileNamePlugin) {
        return new KPVideoShowFileNamePlugin("kplayer", std::move(params));
}
