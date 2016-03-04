#include "game.h"
#include "../../nomad-sdk/source/nomad.h"
#include "../../nomad-sdk/source/events.h"
#include "../../nomad-util/source/log.h"

struct controller_t {
    nomad::object_t & self;

    void think()
    {
    }
};

struct nomad_game_t : public nomad::game_t {
    std::vector<nomad::object_t *> objects_;

    // called for each frame packet received
    void on_frame(const event::game_frame_t & e)
    {
    }

    void on_begin(const event::game_begin_t & e)
    {
        LOGF(log_t::e_log_game, "game begin { seed=%u }", e.seed_);
    }

    virtual void recv(const nomad::event_t & e) override
    {
        switch (e.header_.type_) {
        case (event::e_game_frame):
            on_frame(e.get<event::game_frame_t>());
            break;
        case (event::e_game_begin):
            on_begin(e.get<event::game_begin_t>());
            break;
        }
    }

    virtual nomad::game_view_t * get_view(nomad::player_uuid_t uuid) override;
};

struct nomad_game_view_t : public nomad::game_view_t {
    nomad_game_view_t(nomad_game_t * game, nomad::player_uuid_t uuid)
        : nomad::game_view_t(*game, uuid)
    {
    }

    // query for objects in a rectangular region
    virtual bool query_obj_rect_map(
        const nomad::rect_t &                  in,
        std::vector<const nomad::object_t *> & out) override
    {
        return false;
    }

    // query for objects in a given radius
    virtual bool query_obj_radius_map(
        const nomad::point_t & in, const float radius,
        std::vector<const nomad::object_t *> & out) override
    {
        return false;
    }

    // get map tile information
    virtual bool get_map_info(
        const nomad::rect_t & in, nomad::map_info_t & out) override
    {
        return false;
    }

    // lookup and object by its uuid
    virtual const nomad::object_t * lookup(nomad::object_uuid_t uuid) override
    {
        return nullptr;
    }
};

nomad::game_t * create_game_nomad()
{
    return new nomad_game_t;
}

nomad::game_view_t * nomad_game_t::get_view(nomad::player_uuid_t uuid)
{
    return new nomad_game_view_t(this, uuid);
}
