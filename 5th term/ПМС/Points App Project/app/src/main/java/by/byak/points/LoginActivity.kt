package by.byak.points

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore

class LoginActivity : AppCompatActivity() {
    private lateinit var usernameEditText: EditText
    private lateinit var passwordEditText: EditText

    private lateinit var auth: FirebaseAuth
    private lateinit var firestore: FirebaseFirestore
    val nativeLib = NativeLib()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

        auth = FirebaseAuth.getInstance()
        firestore = FirebaseFirestore.getInstance()

        usernameEditText = findViewById(R.id.username)
        passwordEditText = findViewById(R.id.password)

        val loginButton: Button = findViewById(R.id.loginButton)
        val signUpText: TextView = findViewById(R.id.signUpText)

        loginButton.setOnClickListener {
            val username = usernameEditText.text.toString()
            val password = passwordEditText.text.toString()

            if (nativeLib.isUserValid(username, password))
                Toast.makeText(this, "Невалидный ввод", Toast.LENGTH_LONG)
                    .show()
            else {
                Toast.makeText(this, "Данные введены корректно", Toast.LENGTH_LONG).show()
                val intent = Intent(this, LoginActivity::class.java)
                startActivity(intent)
                finish()
            }
            firestore.collection("users").whereEqualTo("username", username).get()
                .addOnSuccessListener { documents ->
                    if (!documents.isEmpty) {
                        val email = documents.documents[0].getString("email")
                        if (email != null) {
                            auth.signInWithEmailAndPassword(email, password)
                                .addOnCompleteListener(this) { task ->
                                    if (task.isSuccessful) {
                                        val intent = Intent(this@LoginActivity, MainActivity::class.java)
                                        intent.putExtra("openProfile", true)
                                        startActivity(intent)
                                        finish()
                                    } else {
                                        Toast.makeText(
                                            this@LoginActivity,
                                            "Ошибка входа: ${task.exception?.message}",
                                            Toast.LENGTH_SHORT
                                        ).show()
                                    }
                                }
                        }
                    } else {
                        Toast.makeText(this, "Имя пользователя не найдено", Toast.LENGTH_SHORT)
                            .show()
                    }
                }.addOnFailureListener { e ->
                    Toast.makeText(this, "Ошибка поиска: ${e.message}", Toast.LENGTH_SHORT).show()
                }
        }

        signUpText.setOnClickListener {
            val intent = Intent(this@LoginActivity, RegisterActivity::class.java)
            startActivityForResult(intent, REGISTER_REQUEST_CODE)
        }
    }

    companion object {
        const val REGISTER_REQUEST_CODE = 1
    }
}