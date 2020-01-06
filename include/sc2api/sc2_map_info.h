/*! \file sc2_map_info.h
    \brief Information about a game map.
*/
#pragma once

#include "sc2_common.h"
#include "sc2_gametypes.h"

#include "s2clientprotocol/sc2api.pb.h"

#include <string>
#include <vector>

namespace sc2 {

//! Data for a feature layer or rendered image.
struct ImageData {
    int width;
    int height;
    int bits_per_pixel;
    std::string data;

    ImageData();
};

//! Rendered data for a game frame.
struct RenderedFrame {
    ImageData map;
    ImageData minimap;
};

//! Setup structure for feature layers or rendered images.
struct SpatialSetup {
    //! For feature layers only, determines the world space size of the camera.
    float camera_width;
    //! Number of pixels in X of the main game view.
    int map_resolution_x;
    //! Number of pixels in Y of the main game view.
    int map_resolution_y;
    //! Number of pixels in X of the minimap.
    int minimap_resolution_x;
    //! Number of pixels in Y of the minimap.
    int minimap_resolution_y;
};

//! Determines what type of data will be returned in observations.
struct InterfaceOptions {
    //! Raw data; essentially a list of units.
    bool raw;
    //! Feature layer data.
    SpatialSetup feature_layer;
    //! Rendered image data.
    SpatialSetup render;
};

struct PlayerInfo {
    uint32_t player_id;
    PlayerType player_type;
    Race race_requested;
    Race race_actual;
    Difficulty difficulty;
    AIBuild ai_build;
    std::string player_name;

    PlayerInfo(uint32_t player_id, PlayerType player_type,
        Race race_requested, Race race_actual,
        Difficulty difficulty, AIBuild ai_build,
        const std::string& player_name):
        player_id(player_id),
        player_type(player_type),
        race_requested(race_requested),
        race_actual(race_actual),
        difficulty(difficulty),
        ai_build(ai_build),
        player_name(player_name) {};
};

//! Initial data for a game and map.
struct GameInfo {
    //! Plain text name of a map. Note that this may be different from the filename of the map.
    std::string map_name;
    //! Filename of map. Includes the ".SC2Map" file extension.
    std::string local_map_path;
    //! World width of a map.
    int width;
    //! World height of a map.
    int height;
    //! Grid showing which cells are pathable by units.
    ImageData pathing_grid;
    //! Height map of terrain.
    ImageData terrain_height;
    //! Grid showing which cells can accept placement of structures.
    ImageData placement_grid;
    //! The minimum coordinates of playable space. Points less than this are not playable.
    Point2D playable_min;
    //! The maximum coordinates of playable space. Points greater than this are not playable.
    Point2D playable_max;
    //! Positions of possible enemy starting locations.
    std::vector<Point2D> enemy_start_locations;
    std::vector<Point2D> start_locations;

    //! Types of data that will be in observations.
    //!< \sa InterfaceOptions
    InterfaceOptions options;

    std::vector<PlayerInfo> player_info;

    GameInfo();
};

struct SampleImage {
    explicit SampleImage(const SC2APIProtocol::ImageData& data);

    explicit SampleImage(const ImageData& data);

    bool GetBit(const Point2DI& point, bool* dst) const;

    bool GetBit(const Point2DI& point, unsigned char* dst) const;

    int BPP() const;

    Rect2DI Area() const;

private:
    const std::string& data_;
    Rect2DI area_;

    // NOTE (alkurbatov): Possible bits per pixel values specified in
    // protocol/s2clientprotocol/raw.proto
    int bits_per_pixel_;
};

struct PathingGrid {
    explicit PathingGrid(const GameInfo& info);

    bool IsPathable(const Point2DI& point) const;

    void Dump(const std::string& file_path) const;

private:
    SampleImage pathing_grid_;
};

struct PlacementGrid {
    explicit PlacementGrid(const GameInfo& info);

    bool IsPlacable(const Point2DI& point) const;

    void Dump(const std::string& file_path) const;

private:
    SampleImage placement_grid_;
};

struct HeightMap {
    explicit HeightMap(const GameInfo& info);

    float TerrainHeight(const Point2DI& point) const;

    void Dump(const std::string& file_path) const;

private:
    SampleImage height_map_;
};

}
