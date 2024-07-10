//
// Created by Jakub on 08.06.2024.
//
#include <string>
#include <vector>
#include <filesystem>
#ifndef STEGANOGRAFIA_BITTOOL_H
#define STEGANOGRAFIA_BITTOOL_H
#pragma once



std::time_t to_time_t(std::filesystem::file_time_type fileTimeType);
auto generateKEY() -> void;
auto getBitVector(int a, int len) -> std::vector<int>;
auto BitVectorToInt(std::vector<int> vec) -> int;
auto BitLENToInt(std::vector<int> vec) -> int;
auto BitVectorToString(std::vector<int> vec) -> std::string;
auto BOOLFunction(const std::vector<int>& BitVector) -> int;
auto getKeyGEN() -> std::vector<int>;
auto masking(std::vector<int> ch, std::vector<int> keyFrag) -> std::vector<int>;
auto prepareMessage(std::string message) -> std::vector<int>;
auto setComponent(std::vector<int> vectorToChange, std::vector<int> keyFrag )-> int;
#endif //STEGANOGRAFIA_BITTOOL_H
