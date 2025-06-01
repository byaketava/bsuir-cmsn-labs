package by.byak.points

import android.graphics.Color
import android.os.Bundle
import android.text.Spannable
import android.text.SpannableString
import android.text.style.ForegroundColorSpan
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.core.content.ContextCompat
import androidx.core.graphics.drawable.toBitmap
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import by.byak.points.CreateRouteFragment.Companion.MARKERS_INSETS_OPEN_CARD
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.mapbox.geojson.Point
import com.mapbox.maps.CameraOptions
import com.mapbox.maps.MapView
import com.mapbox.maps.MapboxMap
import com.mapbox.maps.Style
import com.mapbox.maps.extension.style.layers.addLayer
import com.mapbox.maps.extension.style.layers.generated.symbolLayer
import com.mapbox.maps.extension.style.layers.properties.generated.IconAnchor
import com.mapbox.maps.extension.style.sources.addSource
import com.mapbox.maps.extension.style.sources.generated.GeoJsonSource
import com.mapbox.maps.extension.style.sources.generated.geoJsonSource
import com.mapbox.maps.extension.style.sources.getSourceAs
import com.mapbox.maps.plugin.annotation.annotations
import com.mapbox.maps.plugin.annotation.generated.PolylineAnnotationManager
import com.mapbox.maps.plugin.annotation.generated.createCircleAnnotationManager
import com.mapbox.maps.plugin.annotation.generated.createPolylineAnnotationManager
import com.mapbox.maps.plugin.locationcomponent.OnIndicatorPositionChangedListener
import com.mapbox.maps.plugin.locationcomponent.location

class RoutesFragment : Fragment() {

    private lateinit var mapView: MapView
    private lateinit var mapboxMap: MapboxMap
    private lateinit var firestore: FirebaseFirestore
    private lateinit var auth: FirebaseAuth
    private lateinit var polylineAnnotationManager: PolylineAnnotationManager
    private lateinit var routesRecyclerView: RecyclerView
    private lateinit var mapMarkersManager: MapMarkersManager

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_routes, container, false)
        firestore = FirebaseFirestore.getInstance()
        auth = FirebaseAuth.getInstance()

        routesRecyclerView = view.findViewById(R.id.routesRecyclerView)
        mapView = view.findViewById(R.id.mapView)
        mapMarkersManager = MapMarkersManager(mapView)

        mapView.mapboxMap.also { mapboxMap ->
            this.mapboxMap = mapboxMap
            mapboxMap.loadStyle(Style.MAPBOX_STREETS) { style ->
                mapView.location.updateSettings {
                    enabled = true  // Включаем использование LocationComponent
                }

                polylineAnnotationManager = mapView.annotations.createPolylineAnnotationManager()
                mapView.location.addOnIndicatorPositionChangedListener(object :
                    OnIndicatorPositionChangedListener {
                    override fun onIndicatorPositionChanged(point: Point) {
                        mapView.mapboxMap.setCamera(
                            CameraOptions.Builder().center(point).zoom(1.0)  // Уровень зума карты
                                .build()
                        )

                        mapView.location.removeOnIndicatorPositionChangedListener(this)
                    }
                })

                fetchUserRoutes()
            }
        }

        mapView.setOnTouchListener { _, event ->
            view.parent?.requestDisallowInterceptTouchEvent(true)
            when (event.action) {
                MotionEvent.ACTION_UP -> view.parent?.requestDisallowInterceptTouchEvent(false)
            }
            false
        }

        routesRecyclerView.layoutManager = LinearLayoutManager(context)
        val routesAdapter = RoutesAdapter(listOf())
        routesRecyclerView.adapter = routesAdapter
        return view
    }

    private fun fetchUserRoutes() {
        val userId = auth.currentUser?.uid
        if (userId != null) {
            firestore.collection("users").document(userId).collection("routes").get()
                .addOnSuccessListener { result ->
                    if (result.isEmpty) {
                        Toast.makeText(context, "Нет сохраненных маршрутов", Toast.LENGTH_SHORT)
                            .show()
                    } else {
                        val routes = mutableListOf<Route>()
                        for (document in result) {
                            val route = document.data

                            val startString = "Откуда: "
                            val endString = "Куда: "

                            val startPointData = route["startPoint"] as? Map<String, Any>
                            val endPointData = route["endPoint"] as? Map<String, Any>

                            val startName = startPointData?.get("name") as? String
                            val endName = endPointData?.get("name") as? String

                            val noteData = route["note"] as? String ?: "Заметка отсутствует"

                            val startPoint = startPointData?.let {
                                val lat = it["latitude"] as? Double ?: 0.0
                                val lng = it["longitude"] as? Double ?: 0.0
                                Point.fromLngLat(lng, lat)  // Создание объекта Point
                            }
                            val endPoint = endPointData?.let {
                                val lat = it["latitude"] as? Double ?: 0.0
                                val lng = it["longitude"] as? Double ?: 0.0
                                Point.fromLngLat(lng, lat)  // Создание объекта Point
                            }


                            val start = SpannableString("$startString$startName")
                            start.setSpan(
                                ForegroundColorSpan(Color.parseColor("#8692F7")),
                                0,
                                startString.length,
                                Spannable.SPAN_EXCLUSIVE_EXCLUSIVE
                            )

                            val end = SpannableString("$endString$endName")
                            end.setSpan(
                                ForegroundColorSpan(Color.parseColor("#8692F7")), // Purple color
                                0, endString.length, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE
                            )

                            if (startPointData != null && endPointData != null) {
                                val startLatitude = (startPointData["latitude"] as? Double) ?: 0.0
                                val startLongitude = (startPointData["longitude"] as? Double) ?: 0.0
                                val endLatitude = (endPointData["latitude"] as? Double) ?: 0.0
                                val endLongitude = (endPointData["longitude"] as? Double) ?: 0.0

                                if (startPoint != null && endPoint != null) {
                                    routes.add(
                                        Route(
                                            start.toString(),
                                            end.toString(),
                                            noteData,
                                            startLatitude,
                                            startLongitude,
                                            endLatitude,
                                            endLongitude
                                        )
                                    )

                                        //drawRouteOnMap(startPoint, endPoint)
                                }
                            }
                        }
                        val adapter = RoutesAdapter(routes)
                        routesRecyclerView.adapter = adapter
                        updateMarkerList(routes)
                    }
                }.addOnFailureListener { e ->
                    Toast.makeText(
                        context, "Ошибка загрузки маршрутов: ${e.message}", Toast.LENGTH_SHORT
                    ).show()
                }
        } else {
            Toast.makeText(context, "Пользователь не аутентифицирован", Toast.LENGTH_SHORT).show()
        }
    }

    private fun updateMarkerList(routes: List<Route>) {
        mapMarkersManager.clearMarkers()
        routes.forEach { route ->
            val startPoint = Point.fromLngLat(route.startLon, route.startLat)
            val endPoint = Point.fromLngLat(route.endLon, route.endLat)

            mapMarkersManager.showMarker(startPoint, true)
            mapMarkersManager.showMarker(endPoint, false)

            drawRouteOnMap(startPoint, endPoint)
        }
    }

    private fun drawRouteOnMap(startPoint: Point, endPoint: Point) {
        if (!::polylineAnnotationManager.isInitialized) {
            return
        }
        val polylineAnnotationOptions =
            com.mapbox.maps.plugin.annotation.generated.PolylineAnnotationOptions()
                .withPoints(listOf(startPoint, endPoint))  // Точки маршрута
                .withLineColor("#8692F7")        // Цвет линии
                .withLineWidth(5.0)              // Толщина линии
        polylineAnnotationManager.create(polylineAnnotationOptions)
    }

    private class MapMarkersManager(private val mapView: MapView) {
        private val mapboxMap = mapView.mapboxMap
        private val circleAnnotationManager =
            mapView.annotations.createCircleAnnotationManager(null)
        private val markers = mutableMapOf<String, Point>()

        private val startMarkerId = "start_point"
        private val endMarkerId = "end_point"

        private val START_SOURCE_ID = "start_source_id"
        private val END_SOURCE_ID = "end_source_id"
        private val START_LAYER_ID = "start_layer_id"
        private val END_LAYER_ID = "end_layer_id"

        fun clearMarkers() {
            markers.clear()
            circleAnnotationManager.deleteAll()
        }

        fun showMarker(coordinate: Point, isStartPoint: Boolean) {
            val iconId = if (isStartPoint) startMarkerId else endMarkerId
            val sourceId = if (isStartPoint) START_SOURCE_ID else END_SOURCE_ID
            val layerId = if (isStartPoint) START_LAYER_ID else END_LAYER_ID

            mapboxMap.getStyle { style ->
                if (style.styleSourceExists(sourceId)) {
                    style.getSourceAs<GeoJsonSource>(sourceId)?.apply {
                        geometry(coordinate)
                    }
                } else {
                    style.addSource(geoJsonSource(sourceId) {
                        geometry(coordinate)
                    })

                    style.addImage(
                        iconId, ContextCompat.getDrawable(
                            mapView.context, R.drawable.round_place_24_red
                        )!!.toBitmap()
                    )
                    style.addLayer(symbolLayer(layerId, sourceId) {
                        iconImage(iconId)
                        iconAnchor(IconAnchor.BOTTOM)
                    })
                }
            }
        }

        fun showMarkers(startCoordinate: Point, endCoordinate: Point) {
            showMarker(startCoordinate, true)
            showMarker(endCoordinate, false)
        }
    }

    override fun onResume() {
        super.onResume()
        fetchUserRoutes()  // Загружаем маршруты при каждом открытии фрагмента
    }

    override fun onStart() {
        super.onStart()
        mapView.onStart()
    }

    override fun onStop() {
        super.onStop()
        mapView.onStop()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        mapView.onDestroy()
    }
}