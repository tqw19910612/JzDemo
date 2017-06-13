/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.eju.cy.jz.app;

import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.eju.cy.jz.tools.SizeHelper;
import com.eju.jz.R;

import org.cocos2dx.lib.Cocos2dxActivity;


public class AppActivity extends Cocos2dxActivity implements Handler.Callback {

    private Handler mHandler;

    private TextView mDataView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mHandler = new Handler(this);

        TextView data = new TextView(this);
        data.setGravity(Gravity.CENTER_VERTICAL);
        data.setPadding(SizeHelper.getSizeByDip(this, 8), 0, 0, 0);
        data.setBackgroundColor(Color.argb(0x80, 0xFF, 0xFF, 0xFF));
        data.setTextColor(Color.BLACK);
        data.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        mDataView = data;

        FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lp.gravity = Gravity.TOP | Gravity.START;

        mFrameLayout.addView(data, lp);
    }

    @Override
    public boolean handleMessage(Message msg) {
        switch (msg.what) {
            case R.id.COCOS_ACTIVITY_UPDATE_DATA: {
                if(null != mDataView) {

                    mDataView.setText("");
                }
                return true;
            }
            default: {
                return false;
            }
        }
    }

    public native void androidSayHello(String b, int a);

    @SuppressWarnings("unused")
    public void CPPSayHello(String b, int a)
    {
//        Log.i("","android收到C++来的数据：b="+b+",a="+a);

        b = b.concat("-android_handled");

        //调用native方法
        androidSayHello(b,a);
    }
}
