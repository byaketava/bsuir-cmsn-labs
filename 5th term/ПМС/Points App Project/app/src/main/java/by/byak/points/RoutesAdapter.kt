package by.byak.points

import android.graphics.Color
import android.text.Spannable
import android.text.SpannableString
import android.text.style.ForegroundColorSpan
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class RoutesAdapter(private val routes: List<Route>) : RecyclerView.Adapter<RoutesAdapter.RouteViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RouteViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.routes_list, parent, false)
        return RouteViewHolder(view)
    }

    override fun onBindViewHolder(holder: RouteViewHolder, position: Int) {
        val route = routes[position]
        holder.bind(route)
    }

    override fun getItemCount(): Int = routes.size

    inner class RouteViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val startPointText: TextView = itemView.findViewById(R.id.startPointText)

        private val endPointText: TextView = itemView.findViewById(R.id.endPointText)
        private val noteText: TextView = itemView.findViewById(R.id.noteText)

        fun bind(route: Route) {
            val startSpannable = SpannableString(route.startPoint)
            startSpannable.setSpan(
                ForegroundColorSpan(Color.parseColor("#8692F7")),
                0,
                "Откуда: ".length,
                Spannable.SPAN_EXCLUSIVE_EXCLUSIVE
            )
            startPointText.text = startSpannable

            val endSpannable = SpannableString(route.endPoint)
            endSpannable.setSpan(
                ForegroundColorSpan(Color.parseColor("#8692F7")),
                0,
                "Куда: ".length,
                Spannable.SPAN_EXCLUSIVE_EXCLUSIVE
            )
            endPointText.text = endSpannable

            noteText.text = route.note
        }
    }
}
