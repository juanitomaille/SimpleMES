static void mask_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    static int16_t mask_top_id = -1;
    static int16_t mask_bottom_id = -1;

    if (code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
        lv_coord_t font_h = lv_font_get_line_height(font);

        lv_area_t roller_coords;
        lv_obj_get_coords(obj, &roller_coords);

        lv_area_t rect_area;
        rect_area.x1 = roller_coords.x1;
        rect_area.x2 = roller_coords.x2;
        rect_area.y1 = roller_coords.y1;
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;

        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *) lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;
        rect_area.y2 = roller_coords.y2;

        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)  lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);

    } else if (code == LV_EVENT_DRAW_POST_END) {
        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)  lv_draw_mask_remove_id(mask_top_id);
        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)  lv_draw_mask_remove_id(mask_bottom_id);
        lv_draw_mask_free_param(fade_mask_top);
        lv_draw_mask_free_param(fade_mask_bottom);
        lv_mem_buf_release(fade_mask_top);
        lv_mem_buf_release(fade_mask_bottom);
        mask_top_id = -1;
        mask_bottom_id = -1;
    }
}

/**
 * Add a fade mask to roller.
 */
void lv_example_roller_3(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_black());
    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_border_width(&style, 0);
    lv_style_set_pad_all(&style, 0);
    lv_obj_add_style(lv_scr_act(), &style, 0);

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act());
    lv_obj_add_style(roller1, &style, 0);
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);

    #if LV_FONT_MONTSERRAT_22
        lv_obj_set_style_text_font(roller1, &lv_font_montserrat_22, LV_PART_SELECTED);
    #endif

    lv_roller_set_options(roller1,
                        "ARRET 1 - Changement d'outil\n"
                        "ARRET 2 - probleme robot\n"
                        "ARRET 3 - Probleme enbarreur\n"
                        "ARRET 4 - probleme bras\n"
                        "ARRET 5 - probleme xxxxx\n"
                        "ARRET 6 - probleme yyyyyyyyyyyyyyyy\n"
                        "ARRET 7 - probleme ssfh bhjj jjjkj\n"
                        "ARRET 8 - robot calé\n"
                        "ARRET 9 - probleme robot\n",
                        LV_ROLLER_MODE_NORMAL);

    lv_obj_center(roller1);
    lv_roller_set_visible_row_count(roller1, 3);
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);
}





// buttons 
void construct_buttons(void)
{
    int button_size = 100;
    int button_alt = 110;
    
    lv_obj_t * ButtonRed = lv_btn_create(lv_scr_act());

    lv_obj_set_size(ButtonRed, button_size, button_size);  // force: 45
    lv_obj_align(ButtonRed, LV_ALIGN_TOP_LEFT, 45, button_alt); // force: 60
    lv_obj_set_style_bg_color(ButtonRed, lv_color_hex(255 * 256 * 256 + 52 * 256 + 16), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonRed, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonRed, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonRed, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonRed, lv_color_hex(255 * 256 * 256 + 52 * 256 + 16), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ButtonRed, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonRed, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonRed, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonRed, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonRed, 0, LV_STATE_DEFAULT);

    lv_obj_t * ButtonOrange = lv_btn_create(lv_scr_act());

    lv_obj_set_size(ButtonOrange, button_size, button_size);  // force: 127
    lv_obj_align(ButtonOrange, LV_ALIGN_TOP_LEFT, 180, button_alt); // force: 60
    lv_obj_set_style_bg_color(ButtonOrange, lv_color_hex(255 * 256 * 256 + 150 * 256 + 0), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonOrange, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonOrange, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonOrange, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonOrange, lv_color_hex(255 * 256 * 256 + 150 * 256 + 0), LV_STATE_DEFAULT );
    lv_obj_set_style_shadow_opa(ButtonOrange, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonOrange, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonOrange, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonOrange, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonOrange, 0, LV_STATE_DEFAULT);

    lv_obj_t * ButtonGreen = lv_btn_create(lv_scr_act());
    lv_obj_set_size(ButtonGreen, button_size, button_size);  // force: 206
    lv_obj_align(ButtonGreen, LV_ALIGN_TOP_LEFT, 320, button_alt); // force: 60
    lv_obj_set_style_bg_color(ButtonGreen, lv_color_hex(0 * 256 * 256 + 255 * 256 + 40), LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ButtonGreen, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonGreen, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonGreen, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonGreen, lv_color_hex(0 * 256 * 256 + 255 * 256 + 40), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ButtonGreen, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonGreen, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonGreen, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonGreen, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonGreen, 0, LV_STATE_DEFAULT);

}
