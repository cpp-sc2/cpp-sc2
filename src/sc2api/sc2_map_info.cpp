#include "sc2api/sc2_map_info.h"

#include <fstream>

namespace sc2 {

ImageData::ImageData () :
    width(0),
    height(0),
    bits_per_pixel(0)
{
}

GameInfo::GameInfo () :
    width(0),
    height(0)
{
}

SampleImage::SampleImage(const SC2APIProtocol::ImageData& data):
    data_(data.data()), area_({0, 0}, {data.size().x(), data.size().y()}),
    bits_per_pixel_(data.bits_per_pixel()) {
}

SampleImage::SampleImage(const ImageData& data):
    data_(data.data), area_({0, 0}, {data.width, data.height}),
    bits_per_pixel_(data.bits_per_pixel) {
}

bool SampleImage::GetBit(const Point2DI& point, bool* dst) const {
    assert(bits_per_pixel_ == 1);

    if (!area_.Contain(point))
        return false;

    div_t idx = div(point.x + point.y * area_.Width(), 8);
    *dst = (data_[idx.quot] >> (7 - idx.rem)) & 1;
    return true;
}

bool SampleImage::GetBit(const Point2DI& point, unsigned char* dst) const {
    assert(bits_per_pixel_ > 1);

    if (!area_.Contain(point))
        return false;

    // Image data is stored with an upper left origin.
    assert(data_.size() == area_.Width() * area_.Height());
    *dst = data_[point.x + point.y * area_.Width()];
    return true;
}

int SampleImage::BPP() const {
    return bits_per_pixel_;
}

Rect2DI SampleImage::Area() const {
    return area_;
}

PathingGrid::PathingGrid(const GameInfo& info):
    pathing_grid_(info.pathing_grid) {
}

bool PathingGrid::IsPathable(const Point2DI& point) const {
    if (pathing_grid_.BPP() == 1) {
        bool value;
        if (!pathing_grid_.GetBit(point, &value))
            return false;

        return value;
    }

    unsigned char value;
    if (!pathing_grid_.GetBit(point, &value))
        return false;

    return value != 255;
}

void PathingGrid::Dump(const std::string& file_path) const {
    std::ofstream dst(file_path);

    for (int y = pathing_grid_.Area().Height() - 1; y >= 0; --y) {
        for (int x = 0; x < pathing_grid_.Area().Width(); ++x) {
            dst << (IsPathable({x, y}) ? ' ' : '#');
        }

        dst << std::endl;
    }
}

PlacementGrid::PlacementGrid(const GameInfo& info):
    placement_grid_(info.placement_grid) {
}

bool PlacementGrid::IsPlacable(const Point2DI& point) const {
    if (placement_grid_.BPP() == 1) {
        bool value;
        if (!placement_grid_.GetBit(point, &value))
            return false;

        return value;
    }

    unsigned char value;
    if (!placement_grid_.GetBit(point, &value))
        return false;

    return value == 255;
}

void PlacementGrid::Dump(const std::string& file_path) const {
    std::ofstream dst(file_path);

    for (int y = placement_grid_.Area().Height() - 1; y >= 0; --y) {
        for (int x = 0; x < placement_grid_.Area().Width(); ++x) {
            dst << (IsPlacable({x, y}) ? ' ' : '#');
        }

        dst << std::endl;
    }
}

HeightMap::HeightMap(const GameInfo& info):
    height_map_(info.terrain_height) {
}

float HeightMap::TerrainHeight(const Point2DI& point) const {
    unsigned char value;
    if (!height_map_.GetBit(point, &value))
        return 0.0f;

    return (static_cast<float>(value) - 127) / 8.f;
}

void HeightMap::Dump(const std::string& file_path) const {
    std::ofstream dst(file_path);

    for (int x = 0; x < height_map_.Area().Width(); ++x) {
        for (int y = 0; y < height_map_.Area().Height(); ++y)
            dst << TerrainHeight({x, y}) << "|";

        dst << std::endl;
    }
}

}
