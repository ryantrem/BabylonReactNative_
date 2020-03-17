package com.reactlibrary;

import android.content.Context;

import androidx.appcompat.widget.AppCompatTextView;

public class ReactTestView extends AppCompatTextView {
    public ReactTestView(Context context) {
        super(context);
        this.setText("this is a native test component");
    }
}
