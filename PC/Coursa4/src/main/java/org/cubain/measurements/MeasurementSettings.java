package org.cubain.measurements;

import org.cubain.objects.NumericalSetting;

import java.util.Map;

public abstract class MeasurementSettings {
    public static final NumericalSetting fileSetting = new NumericalSetting(10000, 50000, 20000);
    public static final NumericalSetting threadSetting = new NumericalSetting(1,20,1);
    public static final String Directory = "src/main/resources";
}
