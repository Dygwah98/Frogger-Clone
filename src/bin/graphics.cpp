#include"../include/graphics.h"

bool Graphics::isValid = false;

bool Graphics::initAllegro() {

    isValid = al_init() and al_install_keyboard();

    return isValid;
}

ALLEGRO_DISPLAY_MODE Graphics::getDispMode() {

    cout << "Graphics::getDispMode() " << this << endl;

    ALLEGRO_DISPLAY_MODE temp;
    al_get_display_mode(0, &temp);

    for(int i = 1; i < al_get_num_display_modes(); ++i) {
        
        al_get_display_mode(i, &temp);
        if(in_range<int>(750, temp.width, 850) and in_range<int>(550, temp.height, 650))
            return temp;
    }

    return temp;
}

Graphics::Graphics(): display(nullptr), timer(nullptr), event_queue(nullptr), redraw(false), key_pressed{Keys::nd} {

    //inizializzazione dell'API di Allegro
    if(!isValid) assert(initAllegro());
    
    //si trovano i parametri adatti per display e timer
    ALLEGRO_DISPLAY_MODE disp = Graphics::getDispMode();
//    cout << disp.format << " " << disp.height << " " << disp.refresh_rate << " " << disp.width << endl;

    //inizializzazione display:
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_refresh_rate(disp.refresh_rate);

    display = al_create_display(disp.width, disp.height);
    assert(display != nullptr);

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    //inizializzazione timer:
    timer = al_create_timer(1.0/disp.refresh_rate);
    assert(timer != nullptr);

    //inizializzazione coda degli eventi:
    event_queue = al_create_event_queue();
    assert(event_queue != nullptr);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_pause_event_queue(event_queue, true);

    cout << "Graphics::Graphics() " << this << endl;
}

Graphics::~Graphics() {
    
    if(display     != nullptr) al_destroy_display(display);
    if(timer       != nullptr) al_destroy_timer(timer);
    if(event_queue != nullptr) al_destroy_event_queue(event_queue);

    cout << "Graphics::~Graphics() " << this << endl;
}

bool Graphics::is_ready() const {

    return isValid and al_get_timer_started(timer) and !al_is_event_queue_paused(event_queue);
}

void Graphics::launch() {

    if(is_ready()) return;

    al_flush_event_queue(event_queue);
    al_start_timer(timer);
    al_pause_event_queue(event_queue, false);
}

void Graphics::suspend() {

    if(!is_ready()) return;
    
    al_stop_timer(timer);
    al_flush_event_queue(event_queue);
    al_pause_event_queue(event_queue, true);
}

Event Graphics::next_event() {

    Event ret = Event::nd;
    
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    
    switch(ev.type) {
        
        case ALLEGRO_EVENT_DISPLAY_CLOSE:

            ret = Event::Exit;
        
        break;

        case ALLEGRO_EVENT_KEY_DOWN:
        
            if(Graphics::keymap.find(ev.keyboard.keycode) != Graphics::keymap.end())
                key_pressed = Graphics::keymap.at(ev.keyboard.keycode);
        
        break;

        case ALLEGRO_EVENT_KEY_UP:
        
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    ret = Event::Exit;
            else if(Graphics::keymap.find(ev.keyboard.keycode) != Graphics::keymap.end())
                if(key_pressed == Graphics::keymap.at(ev.keyboard.keycode))
                    key_pressed = Keys::nd;
        
        break;

        case ALLEGRO_EVENT_TIMER:
        
            if(!redraw) {
                ret = Event::Execute;
                redraw = true;
            
            } else if(al_is_event_queue_empty(event_queue)) {
                ret = Event::Redraw;
                redraw = false;
            }
        
        break;

        default:
        
        break;
    }

    return ret;
}

Keys Graphics::next_key() {

    return key_pressed;
}