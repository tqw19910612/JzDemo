package com.eju.cy.jz.app;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.ViewGroup;

import com.eju.cy.jz.adapter.CustomAdapter;
import com.eju.cy.jz.adapter.CustomAdapter.CustomDataAdapter;
import com.eju.cy.jz.data.CocosData;

import java.util.ArrayList;
import java.util.List;


/**
 * Class description.
 *
 * @author tangqianwei.
 * @date 2017/06/08
 */
public class MainActivity extends Activity implements CocosData, CustomDataAdapter {

    private final String[] LABELS = {
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
        recyclerView.setAdapter(new CustomAdapter(this));

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
    }

    @Override
    public List<CustomAdapter.ClickInterceptor> getClickEvent(int position) {
        switch (position) {
            case 0:
                return ArrayList<String>::new;
        }
    }
}
