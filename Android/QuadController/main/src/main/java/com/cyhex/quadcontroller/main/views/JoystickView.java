package com.cyhex.quadcontroller.main.views;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;

public class JoystickView extends View {

    // Constants
    private final double RAD = 57.2957795;

    // Variables
    private int xPosition = 0; // Touch x position
    private int yPosition = 0; // Touch y position
    private double centerX = 0; // Center view x position
    private double centerY = 0; // Center view y position
    private Paint mainCircle;
    private Paint secondaryCircle;
    private Paint button;
    private Paint horizontalLine;
    private Paint verticalLine;
    private Paint vectorLine;
    private Paint posXY;
    private Paint box;

    private int joystickRadius;
    private int buttonRadius;
    private int lastAngle = 0;

    public JoystickView(Context context) {
        super(context);
    }

    public JoystickView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initJoystickView();
    }

    public JoystickView(Context context, AttributeSet attrs, int defaultStyle) {
        super(context, attrs, defaultStyle);
        initJoystickView();
    }

    protected void initJoystickView() {
        box = new Paint(Paint.ANTI_ALIAS_FLAG);
        box.setColor(Color.DKGRAY);
        box.setStyle(Paint.Style.STROKE);

        mainCircle = new Paint(Paint.ANTI_ALIAS_FLAG);
        mainCircle.setColor(Color.DKGRAY);
        mainCircle.setStyle(Paint.Style.STROKE);

        secondaryCircle = new Paint(Paint.ANTI_ALIAS_FLAG);
        secondaryCircle.setColor(Color.DKGRAY);
        secondaryCircle.setStyle(Paint.Style.STROKE);

        verticalLine = new Paint();
        verticalLine.setStrokeWidth(2);
        verticalLine.setColor(Color.RED);

        horizontalLine = new Paint();
        horizontalLine.setStrokeWidth(2);
        horizontalLine.setColor(Color.GRAY);

        button = new Paint(Paint.ANTI_ALIAS_FLAG);
        button.setColor(Color.RED);
        button.setStyle(Paint.Style.FILL);

        vectorLine = new Paint();
        vectorLine.setStrokeWidth(2);
        vectorLine.setColor(Color.RED);

        posXY = new Paint();
        posXY.setStyle(Paint.Style.STROKE);
        posXY.setColor(Color.GRAY);
        posXY.setTextSize(dp2px(12));
        posXY.setAntiAlias(true);
    }

    @Override
    protected void onFinishInflate() {
    }

    protected int dp2px(int px) {
        return (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, px, getResources().getDisplayMetrics());
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        // setting the measured values to resize the view to a certain width and
        // height
        int d = Math.min(measure(widthMeasureSpec), measure(heightMeasureSpec));

        setMeasuredDimension(d, d);

        // before measure, get the center of view
        if (xPosition == 0 || yPosition == 0) {
            xPosition = getWidth() / 2;
            yPosition = getWidth() / 2;
        }

        buttonRadius = (int) (d / 2 * 0.25);
        joystickRadius = (int) (d / 2 * 0.75);
    }

    private int measure(int measureSpec) {
        int result;

        // Decode the measurement specifications.
        int specMode = MeasureSpec.getMode(measureSpec);
        int specSize = MeasureSpec.getSize(measureSpec);

        if (specMode == MeasureSpec.UNSPECIFIED) {
            // Return a default size of 200 if no bounds are specified.
            result = 200;
        } else {
            // As you want to fill the available space
            // always return the full available bounds.
            result = specSize;
        }
        return result;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        centerX = (getWidth()) / 2;
        centerY = (getHeight()) / 2;

        //wrapping box
        //canvas.drawRect(0,0,canvas.getWidth(), canvas.getHeight(), box);

        // painting the main circle
        canvas.drawCircle((int) centerX, (int) centerY, joystickRadius, mainCircle);

        // painting the secondary circle
        canvas.drawCircle((int) centerX, (int) centerY, joystickRadius / 2, secondaryCircle);

        // paint lines
        canvas.drawLine((float) centerX, (float) centerY + joystickRadius, (float) centerX, (float) (centerY - joystickRadius), horizontalLine);

        canvas.drawLine((float) (centerX - joystickRadius), (float) centerY, (float) (centerX + joystickRadius), (float) centerY, horizontalLine);

        // vector line
        canvas.drawLine((float) centerX, (float) centerY, xPosition, yPosition, vectorLine);

        // painting the move button
        canvas.drawCircle(xPosition, yPosition, buttonRadius, button);

        // posXY text
        canvas.drawText("X:" + getXpos() + " Y:" + getYpos() + " a:" + getAngle() + "°", dp2px(5), dp2px(12), posXY);
    }

    /**
     * update joystick position
     * roll/pitch in Rad
     * @param roll
     * @param pitch
     */
    public void updateData(float roll, float pitch) {
        pitch *= -1;
        roll *= -1;

        // 50 deg for half an axis
        float deg2Local = (float) (joystickRadius/50.0);

        xPosition = (int) (Math.toDegrees(roll) * deg2Local + centerX);
        yPosition = (int) (Math.toDegrees(pitch) * deg2Local + centerY);

        xPosition = ensureRange(xPosition, (int) (centerX - joystickRadius), (int) (centerX + joystickRadius));
        yPosition = ensureRange(yPosition, (int) (centerY - joystickRadius), (int) (centerY + joystickRadius));

        invalidate();
    }

    private int ensureRange(int v, int min, int max) {
        if (v < min) {
            return min;
        }
        if (v > max) {
            return max;
        }
        return v;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        xPosition = (int) event.getX();
        yPosition = (int) event.getY();
        double abs = Math.sqrt((xPosition - centerX) * (xPosition - centerX)
                + (yPosition - centerY) * (yPosition - centerY));
        if (abs > joystickRadius) {
            xPosition = (int) ((xPosition - centerX) * joystickRadius / abs + centerX);
            yPosition = (int) ((yPosition - centerY) * joystickRadius / abs + centerY);
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            xPosition = (int) centerX;
            yPosition = (int) centerY;

        }
        invalidate();
        return true;
    }

    private int getAngle() {
        if (xPosition > centerX) {
            if (yPosition < centerY) {
                return lastAngle = (int) (Math.atan((yPosition - centerY)
                        / (xPosition - centerX))
                        * RAD + 90);
            } else if (yPosition > centerY) {
                return lastAngle = (int) (Math.atan((yPosition - centerY)
                        / (xPosition - centerX)) * RAD) + 90;
            } else {
                return lastAngle = 90;
            }
        } else if (xPosition < centerX) {
            if (yPosition < centerY) {
                return lastAngle = (int) (Math.atan((yPosition - centerY)
                        / (xPosition - centerX))
                        * RAD - 90);
            } else if (yPosition > centerY) {
                return lastAngle = (int) (Math.atan((yPosition - centerY)
                        / (xPosition - centerX)) * RAD) - 90;
            } else {
                return lastAngle = -90;
            }
        } else {
            if (yPosition <= centerY) {
                return lastAngle = 0;
            } else {
                if (lastAngle < 0) {
                    return lastAngle = -180;
                } else {
                    return lastAngle = 180;
                }
            }
        }
    }

    private int getYpos() {
        return (int) ((yPosition - centerY) / joystickRadius * 1024);
    }

    private int getXpos() {
        return (int) ((xPosition - centerX) / joystickRadius * 1024);
    }

}