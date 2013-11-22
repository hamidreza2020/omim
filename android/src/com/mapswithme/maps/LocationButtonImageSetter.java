package com.mapswithme.maps;

import java.util.HashMap;
import java.util.Map;

import android.graphics.drawable.AnimationDrawable;
import android.graphics.drawable.Drawable;
import android.widget.ImageButton;

public class LocationButtonImageSetter
{
  public enum ButtonState
  {
    NO_LOCATION,
    WAITING_LOCATION,
    HAS_LOCATION,
    FOLLOW_MODE
  }

  private final static Map<ButtonState, Integer> STATE_TO_RES = new HashMap<ButtonState, Integer>();
  static
  {
    STATE_TO_RES.put(ButtonState.NO_LOCATION, R.drawable.btn_location_normal);
    STATE_TO_RES.put(ButtonState.HAS_LOCATION, R.drawable.btn_location_pressed);
    STATE_TO_RES.put(ButtonState.FOLLOW_MODE, R.drawable.btn_location_rotation);
    STATE_TO_RES.put(ButtonState.WAITING_LOCATION, R.drawable.btn_map_location_search_anim);
  }

  public static void setButtonViewFromState(ButtonState state, ImageButton button)
  {
    final int id = STATE_TO_RES.get(state);
    final Drawable draw = button.getResources().getDrawable(id);

    button.setImageDrawable(draw);

    if (draw instanceof AnimationDrawable)
      ((AnimationDrawable)draw).start();
  }

}
