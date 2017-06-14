package com.eju.cy.jz.app;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;

import com.eju.cy.jz.adapter.CustomAdapter;
import com.eju.cy.jz.adapter.CustomAdapter.CustomDataAdapter;
import com.eju.cy.jz.data.CocosData;

import java.util.Locale;


/**
 * Class description.
 *
 * @author tangqianwei.
 * @date 2017/06/08
 */
public class MainActivity extends Activity implements CocosData,
        CustomDataAdapter, CustomAdapter.OnItemClickListener {

    private static final String[] LABELS = {
            "goto cocos2dx without data",
            "goto cocos2dx with bundle data",
            "goto cocos2dx with native data"
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        RecyclerView recyclerView = new RecyclerView(this);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(new CustomAdapter(this, this));

        ViewGroup.LayoutParams lp = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        setContentView(recyclerView, lp);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        // access data
    }

    @Override
    public int size() {
        return LABELS.length;
    }

    @Override
    public String getLabel(int position) {
        return LABELS[position % LABELS.length];
//        return String.format(Locale.CHINESE, "item %d", position);
    }

    @Override
    public void onClick(View v, int position) {
        Intent intent = new Intent(this, AppActivity.class);
        switch (position) {
            case 1: {
                intent.putExtra(LINE_WIDTH, 12);
                break;
            }
            case 2: {
                break;
            }
            default: {
                break;
            }
        }
        startActivityForResult(intent, 0x1234);
//        Log.d(this.getLocalClassName(), String.valueOf(position));
    }
}
