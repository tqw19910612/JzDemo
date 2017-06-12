package com.eju.cy.jz.adapter;

import android.content.Context;
import android.graphics.Color;
import android.support.v7.widget.RecyclerView;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.eju.cy.jz.tools.SizeHelper;


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

        View.OnClickListener getClickEvent(int position);
    }

    private CustomDataAdapter mDataAdapter;

    public CustomAdapter(CustomDataAdapter dataAdapter) {
        mDataAdapter = dataAdapter;
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

    static class CustomViewHolder extends RecyclerView.ViewHolder {

        private CustomViewHolder(View itemView) {
            super(itemView);
        }
    }
}
