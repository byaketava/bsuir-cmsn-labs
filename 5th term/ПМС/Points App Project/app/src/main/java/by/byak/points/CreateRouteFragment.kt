package by.byak.points

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.content.res.Resources
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.core.content.ContextCompat
import androidx.core.graphics.drawable.toBitmap
import androidx.core.view.isVisible
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore
import com.mapbox.common.location.AccuracyLevel
import com.mapbox.common.location.DeviceLocationProvider
import com.mapbox.common.location.IntervalSettings
import com.mapbox.common.location.LocationProviderRequest
import com.mapbox.common.location.LocationService
import com.mapbox.common.location.LocationServiceFactory
import com.mapbox.geojson.Point
import com.mapbox.maps.CameraOptions
import com.mapbox.maps.EdgeInsets
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
import com.mapbox.search.autocomplete.PlaceAutocomplete
import com.mapbox.search.autocomplete.PlaceAutocompleteSuggestion
import com.mapbox.search.ui.adapter.autocomplete.PlaceAutocompleteUiAdapter
import com.mapbox.search.ui.view.CommonSearchViewConfiguration
import com.mapbox.search.ui.view.SearchResultsView

class CreateRouteFragment : Fragment() {
    private lateinit var placeAutocomplete: PlaceAutocomplete
    private lateinit var startResultsView: SearchResultsView
    private lateinit var endResultsView: SearchResultsView
    private lateinit var startPlaceAutocompleteUiAdapter: PlaceAutocompleteUiAdapter
    private lateinit var endPlaceAutocompleteUiAdapter: PlaceAutocompleteUiAdapter
    private lateinit var startPointText: EditText
    private lateinit var endPointText: EditText
    private lateinit var noteField: EditText
    private lateinit var mapView: MapView
    private lateinit var mapboxMap: MapboxMap
    private lateinit var mapMarkersManager: MapMarkersManager
    private lateinit var polylineAnnotationManager: PolylineAnnotationManager
    private var ignoreNextQueryUpdate = false
    private var startPoint: Point? = null
    private var endPoint: Point? = null
    private var routeNote: String? = null

    private lateinit var locationProvider: DeviceLocationProvider

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_create_route, container, false)

        val discardButton = view.findViewById<Button>(R.id.discardButton)
        discardButton.setOnClickListener {
            startPointText.text.clear()
            endPointText.text.clear()
            noteField.text.clear()

            mapMarkersManager.clearMarkers()
            polylineAnnotationManager.deleteAll()

            startPoint = null
            endPoint = null

            locationProvider.getLastLocation { location ->
                location?.let {
                    val point = Point.fromLngLat(it.longitude, it.latitude)
                    mapView.getMapboxMap().setCamera(
                        CameraOptions.Builder().center(point).zoom(12.0).build()
                    )
                }
            }
        }

        val saveButton = view.findViewById<Button>(R.id.saveButton)
        saveButton.setOnClickListener {
            if (startPoint != null && endPoint != null) {
                saveRoute(startPoint!!, endPoint!!, routeNote ?: "Заметка отсутствует")
                startPointText.text.clear()
                endPointText.text.clear()
                noteField.text.clear()

                mapMarkersManager.clearMarkers()
                polylineAnnotationManager.deleteAll()

                startPoint = null
                endPoint = null

                locationProvider.getLastLocation { location ->
                    location?.let {
                        val point = Point.fromLngLat(it.longitude, it.latitude)
                        mapView.getMapboxMap().setCamera(
                            CameraOptions.Builder().center(point).zoom(12.0).build()
                        )
                    }
                }
            } else {
                Toast.makeText(
                    requireContext(),
                    "Пожалуйста, выберите начальную и конечную точки",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }

        placeAutocomplete = PlaceAutocomplete.create()
        startPointText = view.findViewById(R.id.startPoint)
        endPointText = view.findViewById(R.id.endPoint)
        noteField = view.findViewById(R.id.noteField)

        mapView = view.findViewById(R.id.mapView)
        mapView.mapboxMap.also { mapboxMap ->
            this.mapboxMap = mapboxMap
            mapboxMap.loadStyle(Style.MAPBOX_STREETS) {
                mapView.location.updateSettings {
                    enabled = true
                }

                polylineAnnotationManager = mapView.annotations.createPolylineAnnotationManager()
                mapView.location.addOnIndicatorPositionChangedListener(object :
                    OnIndicatorPositionChangedListener {
                    override fun onIndicatorPositionChanged(point: Point) {
                        mapView.mapboxMap.setCamera(
                            CameraOptions.Builder().center(point).zoom(12.0).build()
                        )

                        mapView.location.removeOnIndicatorPositionChangedListener(this)
                    }
                })
            }
        }
        mapView.setOnTouchListener { _, event ->
            view.parent?.requestDisallowInterceptTouchEvent(true)
            when (event.action) {
                MotionEvent.ACTION_UP -> view.parent?.requestDisallowInterceptTouchEvent(false)
            }
            false
        }

        mapMarkersManager = MapMarkersManager(mapView)

        startResultsView = view.findViewById(R.id.startResultsView)
        endResultsView = view.findViewById(R.id.endResultsView)

        startResultsView.initialize(
            SearchResultsView.Configuration(
                commonConfiguration = CommonSearchViewConfiguration()
            )
        )
        endResultsView.initialize(
            SearchResultsView.Configuration(
                commonConfiguration = CommonSearchViewConfiguration()
            )
        )

        startPlaceAutocompleteUiAdapter = PlaceAutocompleteUiAdapter(
            view = startResultsView, placeAutocomplete = placeAutocomplete
        )
        endPlaceAutocompleteUiAdapter = PlaceAutocompleteUiAdapter(
            view = endResultsView, placeAutocomplete = placeAutocomplete
        )

        val locationService: LocationService = LocationServiceFactory.getOrCreate()
        val request = LocationProviderRequest.Builder().interval(
            IntervalSettings.Builder().interval(0L).minimumInterval(0L).maximumInterval(0L).build()
        ).displacement(0F).accuracy(AccuracyLevel.HIGHEST).build()

        val result = locationService.getDeviceLocationProvider(request)
        if (result.isValue) {
            locationProvider = result.value!!
            locationProvider.getLastLocation { location ->
                location?.let {
                    val point = Point.fromLngLat(it.longitude, it.latitude)
                    mapView.getMapboxMap().setCamera(
                        CameraOptions.Builder().center(point).zoom(12.0).build()
                    )
                }
            }
        }

        startPlaceAutocompleteUiAdapter.addSearchListener(object :
            PlaceAutocompleteUiAdapter.SearchListener {
            override fun onSuggestionsShown(suggestions: List<PlaceAutocompleteSuggestion>) {}
            override fun onSuggestionSelected(suggestion: PlaceAutocompleteSuggestion) {
                lifecycleScope.launchWhenStarted {
                    placeAutocomplete.select(suggestion).onValue { result ->
                        ignoreNextQueryUpdate = true
                        startPointText.setText(suggestion.name)
                        startPoint = result.coordinate

                        mapMarkersManager.showMarker(result.coordinate, true)

                        startPointText.clearFocus()
                        startPointText.hideKeyboard(requireContext())
                        startResultsView.isVisible = false

                        checkAndBuildRoute()
                    }
                }
            }

            override fun onPopulateQueryClick(suggestion: PlaceAutocompleteSuggestion) {
                startPointText.setText(suggestion.name)
            }

            override fun onError(e: Exception) {}
        })
        endPlaceAutocompleteUiAdapter.addSearchListener(object :
            PlaceAutocompleteUiAdapter.SearchListener {
            override fun onSuggestionsShown(suggestions: List<PlaceAutocompleteSuggestion>) {}
            override fun onSuggestionSelected(suggestion: PlaceAutocompleteSuggestion) {
                lifecycleScope.launchWhenStarted {
                    placeAutocomplete.select(suggestion).onValue { result ->
                        ignoreNextQueryUpdate = true
                        endPointText.setText(suggestion.name)
                        endPoint = result.coordinate

                        mapMarkersManager.showMarker(result.coordinate, false)

                        endPointText.clearFocus()
                        endPointText.hideKeyboard(requireContext())
                        endResultsView.isVisible = false

                        checkAndBuildRoute()
                    }
                }
            }

            override fun onPopulateQueryClick(suggestion: PlaceAutocompleteSuggestion) {
                startPointText.setText(suggestion.name)
            }

            override fun onError(e: Exception) {}
        })

        startPointText.addTextChangedListener(object : TextWatcher {
            override fun onTextChanged(text: CharSequence, start: Int, before: Int, count: Int) {
                if (ignoreNextQueryUpdate) {
                    ignoreNextQueryUpdate = false
                    return
                }

                lifecycleScope.launchWhenStarted {
                    startPlaceAutocompleteUiAdapter.search(text.toString())
                    startResultsView.isVisible = text.isNotEmpty()
                }
            }

            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {}

            override fun afterTextChanged(s: Editable) {}
        })
        endPointText.addTextChangedListener(object : TextWatcher {
            override fun onTextChanged(text: CharSequence, start: Int, before: Int, count: Int) {
                if (ignoreNextQueryUpdate) {
                    ignoreNextQueryUpdate = false
                    return
                }

                lifecycleScope.launchWhenStarted {
                    endPlaceAutocompleteUiAdapter.search(text.toString())
                    endResultsView.isVisible = text.isNotEmpty()
                }
            }

            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {}
            override fun afterTextChanged(s: Editable) {}
        })

        noteField.addTextChangedListener(object : TextWatcher {
            override fun onTextChanged(text: CharSequence, start: Int, before: Int, count: Int) {
                routeNote = text.toString()
            }

            override fun beforeTextChanged(s: CharSequence, start: Int, count: Int, after: Int) {}

            override fun afterTextChanged(s: Editable) {}
        })
        if (!isPermissionGranted(Manifest.permission.ACCESS_FINE_LOCATION)) {
            requestPermissions(
                arrayOf(
                    Manifest.permission.ACCESS_FINE_LOCATION,
                    Manifest.permission.ACCESS_COARSE_LOCATION
                ), PERMISSIONS_REQUEST_LOCATION
            )
        }
        return view
    }

    private fun saveRoute(start: Point, end: Point, note: String) {
        val firestore = FirebaseFirestore.getInstance()
        val userId = getCurrentUserId() // Метод для получения текущего пользователя

        val routeData = hashMapOf(
            "startPoint" to hashMapOf(
                "latitude" to start.latitude(), "longitude" to start.longitude(), "name" to startPointText.text.toString()
            ), "endPoint" to hashMapOf(
                "latitude" to end.latitude(), "longitude" to end.longitude(), "name" to endPointText.text.toString()
            ), "note" to note
        )

        if (userId != null) {
            firestore.collection("users").document(userId).collection("routes").add(routeData)
                .addOnSuccessListener {
                    Toast.makeText(requireContext(), "Маршрут сохранен!", Toast.LENGTH_SHORT).show()
                }.addOnFailureListener { e ->
                    Toast.makeText(
                        requireContext(),
                        "Ошибка сохранения маршрута: ${e.message}",
                        Toast.LENGTH_SHORT
                    ).show()
                }
        }
    }

    private fun getCurrentUserId(): String? {
        return FirebaseAuth.getInstance().currentUser?.uid
    }

    private fun checkAndBuildRoute() {
        if (startPoint != null && endPoint != null) {
            mapMarkersManager.showMarkers(startPoint!!, endPoint!!)
            buildRoute(startPoint!!, endPoint!!)
        }
    }

    private fun buildRoute(start: Point, end: Point) {
        polylineAnnotationManager.deleteAll()

        val polylineAnnotationOptions =
            com.mapbox.maps.plugin.annotation.generated.PolylineAnnotationOptions()
                .withPoints(listOf(start, end))  // Точки маршрута
                .withLineColor("#8692F7")        // Цвет линии
                .withLineWidth(5.0)              // Толщина линии

        polylineAnnotationManager.create(polylineAnnotationOptions)
    }

    private fun isPermissionGranted(permission: String): Boolean =
        ContextCompat.checkSelfPermission(
            requireContext(), permission
        ) == PackageManager.PERMISSION_GRANTED

    private fun View.hideKeyboard(context: Context) =
        (context.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager).hideSoftInputFromWindow(
            windowToken, 0
        )

    companion object {
        const val PERMISSIONS_REQUEST_LOCATION = 0

        val MARKERS_EDGE_OFFSET = dpToPx(64).toDouble()
        val PLACE_CARD_HEIGHT = dpToPx(300).toDouble()
        val MARKERS_TOP_OFFSET = dpToPx(88).toDouble()

        val MARKERS_INSETS_OPEN_CARD = EdgeInsets(
            MARKERS_TOP_OFFSET, MARKERS_EDGE_OFFSET, PLACE_CARD_HEIGHT, MARKERS_EDGE_OFFSET
        )

        private fun dpToPx(dp: Int): Int =
            (dp * Resources.getSystem().displayMetrics.density).toInt()
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

            mapboxMap.setCamera(
                CameraOptions.Builder().center(coordinate) // Центрируем на середине
                    .zoom(10.0) // Устанавливаем зум
                    .padding(MARKERS_INSETS_OPEN_CARD) // Добавляем отступы для маркеров
                    .build()
            )
        }

        fun showMarkers(startCoordinate: Point, endCoordinate: Point) {
            showMarker(startCoordinate, true)
            showMarker(endCoordinate, false)
        }
    }
}
