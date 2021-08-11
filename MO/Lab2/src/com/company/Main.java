package com.company;

interface FunctionStrategy {
    double calc(double x);

    void printTotalCalls();
}

abstract class Function implements FunctionStrategy {
    protected int calls = 0;

    @Override
    public double calc(double x) {
        return 0;
    }

    @Override
    public void printTotalCalls() {
    }
}

class GoldenSectionSearch {
    private double leftBound;
    private double rightBound;
    private double epsilon;
    private double xMin;
    private static FunctionStrategy function;
    private static GoldenSectionSearch obj = null;
    private final double LEFT_CONST = 0.328;
    private final double RIGHT_CONST = 0.618;
    private final int MAX_NUM_OF_ITERATIONS = 1000;

    private GoldenSectionSearch() {
        leftBound = rightBound = epsilon = xMin = 0.0;
    }

    public static GoldenSectionSearch get() {
        if (GoldenSectionSearch.obj == null) {
            GoldenSectionSearch.obj = new GoldenSectionSearch();
        }
        return GoldenSectionSearch.obj;
    }

    public void process() {
        int it = 0;
        if (ifCorrectBoundsOrder() && this.epsilon > 0) {
            double segmentLength = this.rightBound - this.leftBound;
            double x1 = this.leftBound + LEFT_CONST * segmentLength;
            double x2 = this.leftBound + RIGHT_CONST * segmentLength;
            double f1 = function.calc(x1);
            double f2 = function.calc(x2);
            printIterationResults(it, x1, x2, f1, f2, segmentLength);
            while ((this.rightBound - this.leftBound) > this.epsilon && it < MAX_NUM_OF_ITERATIONS) {
                if (f1 > f2) {
                    this.leftBound = x1;
                    segmentLength = this.rightBound - this.leftBound;
                    x1 = x2;
                    f1 = f2;
                    x2 = this.leftBound + RIGHT_CONST * segmentLength;
                    f2 = function.calc(x2);
                } else {
                    this.rightBound = x2;
                    segmentLength = this.rightBound - this.leftBound;
                    x2 = x1;
                    f2 = f1;
                    x1 = this.leftBound + LEFT_CONST * segmentLength;
                    f1 = function.calc(x1);
                }
                it++;
                printIterationResults(it, x1, x2, f1, f2, segmentLength);
            }
            xMin = (this.leftBound + this.rightBound) / 2.0f;
            System.out.println("Found XMIN -> " + xMin);
        } else {
            System.out.println("Incorrect border orders -> " + "left: " + getLeftBound() + " right: " + getRightBound() + "\nEpsilon: " + this.epsilon);
        }
    }

    private void printIterationResults(int it, double x1, double x2, double f1, double f2, double length) {
        System.out.println("IT: " + it + ", x1 = " + x1 + ", x2 = " + x2 + ", f1 = " + f1 + ", f2 = " + f2 + ", L =" + length);
    }

    private boolean ifCorrectBoundsOrder() {
        return getLeftBound() < getRightBound();
    }

    public GoldenSectionSearch setLeftBound(double newLeftBound) {
        this.leftBound = newLeftBound;
        return get();
    }

    public GoldenSectionSearch setRightBound(double newRightBound) {
        this.rightBound = newRightBound;
        return get();
    }

    public double getLeftBound() {
        return this.leftBound;
    }

    public double getRightBound() {
        return this.rightBound;
    }

    public GoldenSectionSearch setEpsilon(double newEpsilon) {
        this.epsilon = newEpsilon;
        return get();
    }

    public GoldenSectionSearch setFunction(FunctionStrategy func) {
        GoldenSectionSearch.function = func;
        return get();
    }
}

class DSKAlgorithm {
    private double startPoint;
    private double startStep;
    private FunctionStrategy function = null;
    private static DSKAlgorithm obj = null;
    private double leftBound;
    private double rightBound;
    private final int MAX_STEP_COUNT = 20;
    private boolean foundFeedback = false;

    DSKAlgorithm() {
        startPoint = 0;
        leftBound = 0;
        rightBound = 0;
    }

    public static DSKAlgorithm get() {
        if (DSKAlgorithm.obj == null) {
            DSKAlgorithm.obj = new DSKAlgorithm();
        }
        return DSKAlgorithm.obj;
    }

    public DSKAlgorithm setStartPoint(double x0) {
        this.startPoint = x0;
        return DSKAlgorithm.obj;
    }

    public DSKAlgorithm setStartStep(double step) {
        this.startStep = step;
        return DSKAlgorithm.obj;
    }

    public DSKAlgorithm setFunction(FunctionStrategy function) {
        this.function = function;
        return DSKAlgorithm.obj;
    }

    public double getRightBound() {
        return this.rightBound;
    }

    public double getLeftBound() {
        return this.leftBound;
    }

    public DSKAlgorithm searchBounds() {
        double x0 = startPoint;
        double x1 = startPoint - startStep;
        double x2 = startPoint + startStep;
        double f0 = function.calc(x0);
        double f1 = function.calc(x1);
        double f2 = function.calc(x2);
        if (f1 > f0 && f2 > f0) {
            leftBound = x1;
            rightBound = x2;
            return DSKAlgorithm.obj;
        } else if (f1 < f0 && f2 < f0) {
            System.out.println("The function is not unimodal in the initial interval: interval { " + x1 + ", " + x2 + " }");
        }
        if (f1 <= f2) {
            startStep = -startStep;
        } else {
            x1 = x2;
            f1 = f2;
        }
        for (int i = 1; i < MAX_STEP_COUNT; ++i) {
            startStep = 2 * startStep;
            x2 = x1 + startStep;
            f2 = function.calc(x2);
            if (f2 <= f1) {
                x0 = x1;
                x1 = x2;
                f1 = f2;
            } else {
                double x3 = x2 - startStep / 2;
                double f3 = function.calc(x3);
                if (f1 > f3) {
                    leftBound = x1;
                    rightBound = x2;
                } else {
                    leftBound = x0;
                    rightBound = x3;
                }
                if (leftBound > rightBound) {
                    double temp = leftBound;
                    leftBound = rightBound;
                    rightBound = temp;
                }
                foundFeedback = true;
                return DSKAlgorithm.obj;
            }
        }
        foundFeedback = false;
        System.out.println("Start point (" + startPoint + ") is too far from the minimum point");
        return DSKAlgorithm.obj;
    }

    public boolean isLastFound() {
        return this.foundFeedback;
    }
}

class QuadraticFunction extends Function {
    @Override
    public double calc(double x) {
        calls++;
        return x * x - 11 * x + 18;
    }

    @Override
    public void printTotalCalls() {
        System.out.println("Quadratic function calls: " + calls);
        resetCallsCounter();
    }

    public void resetCallsCounter() {
        calls = 0;
    }
}

class NonQuadraticFunction extends Function {
    @Override
    public double calc(double x) {
        calls++;
        return x * (x * x + Math.sin(x));
    }

    @Override
    public void printTotalCalls() {
        System.out.println("Non-quadratic function calls: " + calls);
        resetCallsCounter();
    }

    public void resetCallsCounter() {
        calls = 0;
    }
}

public class Main {
    public static void main(String[] args) {
        GoldenSectionSearch algo = GoldenSectionSearch.get();
        FunctionStrategy quadraticFunc = new QuadraticFunction();
        FunctionStrategy nonQuadraticFunc = new NonQuadraticFunction();
        DSKAlgorithm svenn = DSKAlgorithm.get();
        double leftBound;
        double rightBound;
        for (double i = 10E-2; i > 10E-5; i *= 10E-2) {
            System.out.println("Start step: " + i);
            svenn.setStartStep(i).setFunction(quadraticFunc).setStartPoint(2.0).searchBounds();
            leftBound = svenn.getLeftBound();
            rightBound = svenn.getRightBound();
            quadraticFunc.printTotalCalls();
            if (svenn.isLastFound()) {
                System.out.println("Found bounds: a -> " + leftBound + ", b -> " + rightBound);
                algo.setEpsilon(1E-3).setFunction(quadraticFunc).setLeftBound(leftBound).setRightBound(rightBound).process();
                quadraticFunc.printTotalCalls();
            }
            System.out.println();
            svenn.setStartStep(i).setFunction(nonQuadraticFunc).setStartPoint(-0.2).searchBounds();
            leftBound = svenn.getLeftBound();
            rightBound = svenn.getRightBound();
            nonQuadraticFunc.printTotalCalls();
            if (svenn.isLastFound()) {
                System.out.println("Found bounds: a -> " + leftBound + ", b -> " + rightBound);
                algo.setEpsilon(1E-3).setFunction(nonQuadraticFunc).setLeftBound(leftBound).setRightBound(rightBound).process();
                nonQuadraticFunc.printTotalCalls();
            }
        }
    }
}
