package by.byak.points

data class Route(
    val startPoint: String,
    val endPoint: String,
    val note: String,
    val startLat: Double,
    val startLon: Double,
    val endLat: Double,
    val endLon: Double
)