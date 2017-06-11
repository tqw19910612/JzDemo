package com.eju.cy.jz.tools;

import android.content.Context;
import android.util.DisplayMetrics;
import android.util.TypedValue;

/**
 * Class description.
 *
 * @author tangqianwei.
 * @date 2017/06/08
 */
public class SizeHelper {

    public static int getSizeByDip(Context context, float value) {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        return (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, value, metrics);
    }

    public static int getScreenHeight(Context context) {
        return context.getResources().getDisplayMetrics().heightPixels;
    }

    public static int getScreenWidth(Context context) {
        return context.getResources().getDisplayMetrics().widthPixels;
    }
}
