package by.byak.points

class NativeLib {
    init {
        System.loadLibrary("points")
    }

    external fun addUser(username: String, password: String): Boolean
    external fun isUserValid(username: String, password: String): Boolean
    external fun isUserExists(username: String): Boolean
}