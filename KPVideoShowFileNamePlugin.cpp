//
// Created by karaler on 2019-10-29.
// Author: karaler
// Description:
// Others: 
// Copyright (c) 2019 ${ORGANIZATION_NAME}. All rights reserved.
//

#include "KPVideoShowFileNamePlugin.h"

KPVideoShowFileNamePlugin::KPVideoShowFileNamePlugin(const std::string &identify_name, const std::string &filter_name, const KPFilterType &filter_type, PluginParamsObject plugin_params_object) : KPPluginAdapter(identify_name, filter_name, filter_type, plugin_params_object) {
    // 赋值described
    std::stringstream filter_desc_stream;


    if (plugin_params_object.params.find("font_size") != plugin_params_object.params.end()) {
        font_size = plugin_params_object.params["font_size"];
    }
    if (plugin_params_object.params.find("font_color") != plugin_params_object.params.end()) {
        font_color = plugin_params_object.params["font_color"];
    }
    if (plugin_params_object.params.find("x") != plugin_params_object.params.end()) {
        x = plugin_params_object.params["x"];
    }
    if (plugin_params_object.params.find("y") != plugin_params_object.params.end()) {
        y = plugin_params_object.params["y"];
    }
    if (plugin_params_object.params.find("show_extension") != plugin_params_object.params.end()) {
        show_extension = plugin_params_object.params["show_extension"];
    }

    filter_desc_stream << "x=" << x << ":y=" << y << ":fontfile=res/font.ttf:fontsize=" << font_size << ":fontcolor=" << font_color << ":text='" << "[无]" << "'";

    filter_desc = filter_desc_stream.str();

    // 查找过滤器
    filter = avfilter_get_by_name("drawtext");
    if (filter == nullptr)
        throw KPFilterException("未知过滤器; filter name: drawtext");
}

KPVideoShowFileNamePlugin::~KPVideoShowFileNamePlugin() {
    global_event_play_updated.Unsubscribe(event_id);
}

void KPVideoShowFileNamePlugin::Task() {
    // 初始化当前文件名
    auto current_title = global_event_play_updated.GetLastVariable();
    ChangeTitle(current_title);


    // 监听下一次文件播放更改
    event_id = global_event_play_updated.Subscribe([&](const std::string &file_path) {
        ChangeTitle(file_path);
    });
}

void KPVideoShowFileNamePlugin::KillTask() {
}

void KPVideoShowFileNamePlugin::InitTask() {
    // 初始化当前文件名
    auto current_title = global_event_play_updated.GetLastVariable();
    ChangeTitle(current_title);
}

int KPVideoShowFileNamePlugin::ChangeTitle(const std::string &file_path) {
    KPlayer::FileInfo                  file_info(file_path);
    std::string                        title = show_extension == "1" ? file_info.GetFileName() : file_info.GetBaseFileName();
    std::map<std::string, std::string> value{{"text", title}};

    return SetPluginValue(value);
}

KPLAYER_PLUGIN_FUNC(KPVideoShowFileNamePlugin) {
    return new KPVideoShowFileNamePlugin("kplayer", "video_plugin_show_file_name", KP_FILTER_TYPE_VIDEO, std::move(plugin_params));
}
