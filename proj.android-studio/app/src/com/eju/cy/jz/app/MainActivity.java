package com.eju.cy.jz.app;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.eju.cy.jz.data.CocosData;
import com.eju.jz.AppActivity;

import java.util.ArrayList;
import java.util.List;


/**
 * Class description.
 *
 * @author tangqianwei.
 * @date 2017/06/08
 */
public class MainActivity extends Activity implements CocosData {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        RecyclerView recyclerView = new RecyclerView(this);
        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(new CustomAdapter(new CustomDataAdapter() {

            private final String[] LABELS = {
                    "goto cocos2dx without data",
                    "goto cocos2dx with bundle data",
                    "goto cocos2dx with native data"
            };
            private final ClickInterceptor[] INTERCEPTORS = {
                    null,
                    new ClickInterceptor() {
                        @Override
                        public Intent intercept(Chain chain) throws Exception {
                            Intent intent = chain.getIntent();
                            intent.putExtra(LINE_WIDTH, 12);
                            return chain.proceed(intent);
                        }
                    },
                    null
            };
            private final InterceptorClickListener listener =
                    new InterceptorClickListener(MainActivity.this);

            @Override
            public int size() {
                return LABELS.length;
            }

            @Override
            public String getLabel(int position) {
                return LABELS[position % LABELS.length];
            }

            @Override
            public View.OnClickListener getClickEvent(int position) {
                listener.clearClickInterceptors();
                listener.addClickInterceptor(INTERCEPTORS[position]);
                return listener;
            }

        }));

        ViewGroup.LayoutParams lp = new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        setContentView(recyclerView, lp);
    }

    private static class InterceptorClickListener implements View.OnClickListener {

        private List<ClickInterceptor> interceptors = new ArrayList<>();
        private Context mContext;

        private InterceptorClickListener(Context context) {
            this.mContext = context;
        }

        private void addClickInterceptor(ClickInterceptor interceptor) {
            if(null == interceptor) {
                return;
            }

            this.interceptors.add(interceptor);
        }

        private void clearClickInterceptors() {
            this.interceptors.clear();
        }


        @Override
        public void onClick(View v) {
            Intent origin = new Intent(mContext, AppActivity.class);
            ClickInterceptor.Chain chain = new ClickInterceptor.Chain(
                    0, interceptors.toArray(new ClickInterceptor[interceptors.size()]), origin);
            try {
                Intent intent = chain.proceed(origin);
                mContext.startActivity(null == intent ? origin : intent);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private interface ClickInterceptor {
        Intent intercept(Chain chain) throws Exception;

        class Chain {

            private ClickInterceptor[] interceptors;
            private int index;
            private Intent intent;

            private Chain(int index, ClickInterceptor[] interceptors, Intent intent) {
                this.index = index;
                this.interceptors = interceptors;
                this.intent = intent;
            }

            private Intent getIntent() {
                return this.intent;
            }

            private Intent proceed(Intent intent) throws Exception {
                if(null == this.interceptors
                        || 0 == this.interceptors.length
                        || this.interceptors.length <= index) {
                    return intent;
                }

                ClickInterceptor interceptor = this.interceptors[index];
                Chain next = new Chain(index + 1, interceptors, intent);
                return interceptor.intercept(next);
            }
        }
    }

    private static class CustomViewHolder extends RecyclerView.ViewHolder {

        private CustomViewHolder(View itemView) {
            super(itemView);
        }
    }

    private static class CustomAdapter extends RecyclerView.Adapter<CustomViewHolder> {

        private CustomDataAdapter mDataAdapter;

        private CustomAdapter(CustomDataAdapter dataAdapter) {
            mDataAdapter = dataAdapter;
        }

        @Override
        public CustomViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            Context context = parent.getContext();
            DisplayMetrics metrics = context.getResources().getDisplayMetrics();
            TextView view = new TextView(parent.getContext());
            view.setLayoutParams(new ViewGroup.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT,
                    metrics.heightPixels / 5));
            view.setBackgroundColor(Color.WHITE);
            view.setGravity(Gravity.CENTER_VERTICAL);
            view.setPadding(getDipHeight(metrics, 6), 0, 0, 0);
            view.setTextColor(Color.BLACK);
            view.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
            return new CustomViewHolder(view);
        }

        @Override
        public void onBindViewHolder(CustomViewHolder holder, int position) {
            TextView view = (TextView)holder.itemView;
            view.setText(mDataAdapter.getLabel(position));
            view.setOnClickListener(mDataAdapter.getClickEvent(position));
        }

        @Override
        public int getItemCount() {
            return mDataAdapter.size();
        }

        private int getDipHeight(DisplayMetrics metrics, int value) {
            return (int)TypedValue.applyDimension(
                    TypedValue.COMPLEX_UNIT_DIP,
                    value,
                    metrics);
        }
    }

    private interface CustomDataAdapter {

        int size();

        String getLabel(int position);

        View.OnClickListener getClickEvent(int position);
    }
}
