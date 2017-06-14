package com.eju.cy.jz.adapter;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.support.v7.widget.RecyclerView;
import android.util.SparseArray;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.eju.cy.jz.tools.SizeHelper;

import java.util.ArrayList;
import java.util.List;


/**
 * Class description.
 *
 * @author tangqianwei.
 * @date 2017/06/08
 */
public class CustomAdapter extends RecyclerView.Adapter<CustomAdapter.CustomViewHolder> {

    public interface CustomDataAdapter {

        int size();

        String getLabel(int position);
    }

    public interface OnItemClickListener {

        void onClick(View v, int position);
    }


    private CustomDataAdapter mDataAdapter;
    private OnItemClickListener mItemClickListener;

    public CustomAdapter(CustomDataAdapter dataAdapter, OnItemClickListener itemClickListener) {
        mDataAdapter = dataAdapter;
        mItemClickListener = itemClickListener;
    }

    @Override
    public CustomViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        Context context = parent.getContext();

        TextView view = new TextView(context);
        view.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                SizeHelper.getScreenHeight(context) / 8));
        view.setBackgroundColor(Color.WHITE);
        view.setGravity(Gravity.CENTER_VERTICAL);
        view.setPadding(SizeHelper.getSizeByDip(context, 6), 0, 0, 0);
        view.setTextColor(Color.BLACK);
        view.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);

        return new CustomViewHolder(view, mItemClickListener);
    }

    @Override
    public void onBindViewHolder(CustomViewHolder holder, int position) {
        TextView view = (TextView)holder.itemView;
        view.setText(mDataAdapter.getLabel(position));
    }

    @Override
    public int getItemCount() {
        return mDataAdapter.size();
    }

    static class CustomViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private OnItemClickListener mItemClickListener;

        private CustomViewHolder(View itemView, OnItemClickListener itemClickListener) {
            super(itemView);
            itemView.setOnClickListener(this);

            mItemClickListener = itemClickListener;
        }

        @Override
        public void onClick(View v) {
//            int adapterPosition = this.getAdapterPosition();
//            int layoutPosition = this.getLayoutPosition();
//
//            Log.d("item", String.format("[%d, %d]", adapterPosition, layoutPosition));

            if (null != mItemClickListener) {
                mItemClickListener.onClick(v, this.getAdapterPosition());
            }
        }
    }

    public interface ClickInterceptor {
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

    public static class InterceptorClickListener implements View.OnClickListener {

        private SparseArray<ClickInterceptor[]> interceptors = new SparseArray<>();
        private Context mContext;

        public InterceptorClickListener(Context context) {
            this.mContext = context;
        }

        private void addClickInterceptor(int position, List<ClickInterceptor> interceptor) {
            if(null == interceptor) {
                interceptor = new ArrayList<>();
            }

            this.interceptors.put(position,
                    interceptor.toArray(new ClickInterceptor[interceptor.size()]));
        }

        private void clearClickInterceptors() {
            this.interceptors.clear();
        }


        @Override
        public void onClick(View v) {
//            Intent origin = new Intent(mContext, AppActivity.class);
//            ClickInterceptor.Chain chain = new ClickInterceptor.Chain(
//                    0, interceptors.toArray(new ClickInterceptor[interceptors.size()]), origin);
//            try {
//                Intent intent = chain.proceed(origin);
//                mContext.startActivity(null == intent ? origin : intent);
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
        }
    }
}
