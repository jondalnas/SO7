import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.chribuhbrojen.SO7.R;

import java.util.ArrayList;

public class DeviceListAdapter extends ArrayAdapter<String> {
    public DeviceListAdapter(Context context, ArrayList<String> objects) {
        super(context, 0, objects);
    }

    @Override
    public View getView(int position, View view, ViewGroup viewGroup) {
        String str = getItem(position);


        return view;
    }
}
