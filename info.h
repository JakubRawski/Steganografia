//
// Created by Jakub on 26.05.2024.
//
#include <ctime>
#include <filesystem>
#ifndef STEGANOGRAFIA_INFO_H
#define STEGANOGRAFIA_INFO_H



#pragma once

std::time_t to_time_t(std::filesystem::file_time_type fileTimeType);
auto Info(const std::string& path) ->void;

#endif //STEGANOGRAFIA_INFO_H
