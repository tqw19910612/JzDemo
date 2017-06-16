package com.eju.cy.jz.app;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.AppBarLayout;
import android.support.design.widget.CoordinatorLayout;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.util.TypedValue;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import com.eju.cy.jz.R;
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
public class MainActivity extends AppCompatActivity implements CocosData,
        CustomDataAdapter, CustomAdapter.OnItemClickListener {

//    private static final String[] LABELS = {
//            "goto cocos2dx without data",
//            "goto cocos2dx with bundle data",
//            "goto cocos2dx with native data"
//    };

    private CustomAdapter mAdapter;
    private int mListSize = 5;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(onCreateView());
    }

    @NonNull protected View onCreateView() {

        CoordinatorLayout root = new CoordinatorLayout(this);

        AppBarLayout barContainer = new AppBarLayout(this);
        Toolbar toolbar = new Toolbar(this);
        toolbar.setTitle(R.string.app_name);
        toolbar.setBackgroundColor(Color.parseColor("#3F51B5"));
        AppBarLayout.LayoutParams toobarLayoutParams = new AppBarLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, getActionBarSize());
        barContainer.addView(toolbar,toobarLayoutParams);
        CoordinatorLayout.LayoutParams barContainerLayoutParams = new CoordinatorLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        root.addView(barContainer, barContainerLayoutParams);
        setSupportActionBar(toolbar);

//        LinearLayout buttonPane = new LinearLayout(this);
//        buttonPane.setOrientation(LinearLayout.HORIZONTAL);
//        LinearLayout.LayoutParams buttonPaneLayoutParams = new LinearLayout.LayoutParams(
//                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
//        root.addView(buttonPane, buttonPaneLayoutParams);
//
//        Button addButton = new Button(this);
//        addButton.setId(R.id.ACTIVITY_MAIN_BUTTON_ADD);
//        addButton.setText("add");
//        addButton.setOnClickListener(this);
//        addButton.setGravity(Gravity.CENTER_VERTICAL);
//        LinearLayout.LayoutParams addButtonLayoutParams = new LinearLayout.LayoutParams(
//                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
//        buttonPane.addView(addButton, addButtonLayoutParams);
//
//        Button removeButton = new Button(this);
//        removeButton.setId(R.id.ACTIVITY_MAIN_BUTTON_REMOVE);
//        removeButton.setText("remove");
//        removeButton.setOnClickListener(this);
//        removeButton.setGravity(Gravity.CENTER_VERTICAL);
//        LinearLayout.LayoutParams removeButtonLayoutParams = new LinearLayout.LayoutParams(
//                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
//        buttonPane.addView(removeButton, removeButtonLayoutParams);

        RecyclerView recyclerView = new RecyclerView(this);
        recyclerView.setHasFixedSize(true);
        recyclerView.setBackgroundColor(Color.WHITE);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(mAdapter = new CustomAdapter(this, this));
        recyclerView.setOverScrollMode(View.OVER_SCROLL_NEVER);

        RecyclerView.ItemAnimator defaultAnimator = recyclerView.getItemAnimator();
        recyclerView.setItemAnimator(new CustomAnimator(defaultAnimator));

        CoordinatorLayout.LayoutParams lp = new CoordinatorLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        lp.setBehavior(new AppBarLayout.ScrollingViewBehavior());
        root.addView(recyclerView, lp);

        return root;
    }

    private int getActionBarSize() {
        TypedValue value = new TypedValue();
        if(getTheme().resolveAttribute(R.attr.actionBarSize, value, true)) {
            return TypedValue.complexToDimensionPixelSize(
                    value.data, getResources().getDisplayMetrics());
        }
        return (int)TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP, 56, getResources().getDisplayMetrics());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.MAIN_ACTION_ADD: {
                mAdapter.notifyItemInserted(mListSize);
                mListSize++;
                return true;
            }
            case R.id.MAIN_ACTION_REMOVE: {
                if(0 < mListSize) {
                    mAdapter.notifyItemRemoved(mListSize + 1);
                    mListSize--;
                }
                return true;
            }
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        // access data
    }

    @Override
    public int size() {
//        return LABELS.length;
        Log.d("ADAPTER", mListSize+"");
        return mListSize;
    }

    @Override
    public String getLabel(int position) {
//        return LABELS[position % LABELS.length];
        return String.format(Locale.CHINESE, "item %d", position);
    }

    @Override
    public void onClick(View v, int position) {
//        Intent intent = new Intent(this, AppActivity.class);
//        switch (position) {
//            case 1: {
//                intent.putExtra(LINE_WIDTH, 12);
//                break;
//            }
//            case 2: {
//                break;
//            }
//            default: {
//                break;
//            }
//        }
//        startActivityForResult(intent, 0x1234);
//        Log.d(this.getLocalClassName(), String.valueOf(position));
    }

    private static class CustomAnimator extends RecyclerView.ItemAnimator {

        private static final String TAG = "CustomAnimator";
        private RecyclerView.ItemAnimator animator;

        private CustomAnimator(RecyclerView.ItemAnimator animator) {
            this.animator = animator;
        }

        @Override
        public boolean animateDisappearance(@NonNull RecyclerView.ViewHolder viewHolder,
                                            @NonNull ItemHolderInfo preLayoutInfo,
                                            @Nullable ItemHolderInfo postLayoutInfo) {
            Log.d(TAG, "animateDisappearance");
            return animator.animateDisappearance(viewHolder, preLayoutInfo, postLayoutInfo);
        }

        @Override
        public boolean animateAppearance(@NonNull RecyclerView.ViewHolder viewHolder,
                                         @Nullable ItemHolderInfo preLayoutInfo,
                                         @NonNull ItemHolderInfo postLayoutInfo) {
            Log.d(TAG, "animateAppearance");
            return animator.animateAppearance(viewHolder, preLayoutInfo, postLayoutInfo);
        }

        @Override
        public boolean animatePersistence(@NonNull RecyclerView.ViewHolder viewHolder,
                                          @NonNull ItemHolderInfo preLayoutInfo,
                                          @NonNull ItemHolderInfo postLayoutInfo) {
            Log.d(TAG, "animatePersistence");
            return animator.animatePersistence(viewHolder, preLayoutInfo, postLayoutInfo);
        }

        @Override
        public boolean animateChange(@NonNull RecyclerView.ViewHolder oldHolder,
                                     @NonNull RecyclerView.ViewHolder newHolder,
                                     @NonNull ItemHolderInfo preLayoutInfo,
                                     @NonNull ItemHolderInfo postLayoutInfo) {
            Log.d(TAG, "animateChange");
            return animator.animateChange(oldHolder, newHolder, preLayoutInfo, postLayoutInfo);
        }

        @Override
        public void runPendingAnimations() {
            Log.d(TAG, "runPendingAnimations");
            animator.runPendingAnimations();
        }

        @Override
        public void endAnimation(RecyclerView.ViewHolder item) {
            Log.d(TAG, "endAnimation");
            animator.endAnimation(item);
        }

        @Override
        public void endAnimations() {
            Log.d(TAG, "endAnimations");
            animator.endAnimations();
        }

        @Override
        public boolean isRunning() {
            Log.d(TAG, "isRunning");
            return animator.isRunning();
        }
    }
}
