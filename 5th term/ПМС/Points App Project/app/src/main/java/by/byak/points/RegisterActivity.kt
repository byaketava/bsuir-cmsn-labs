package by.byak.points

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore

class RegisterActivity : AppCompatActivity() {
    private lateinit var auth: FirebaseAuth
    private lateinit var firestore: FirebaseFirestore

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register)

        auth = FirebaseAuth.getInstance()
        firestore = FirebaseFirestore.getInstance()

        val registerUsername: EditText = findViewById(R.id.registerUsername)
        val registerEmail: EditText = findViewById(R.id.registerEmail)
        val registerPassword: EditText = findViewById(R.id.registerPassword)
        val registerButton: Button = findViewById(R.id.registerButton)


        registerButton.setOnClickListener {
            val username = registerUsername.text.toString()
            val email = registerEmail.text.toString()
            val password = registerPassword.text.toString()

            if (isPasswordValid(password)) {
                auth.createUserWithEmailAndPassword(email, password)
                    .addOnCompleteListener(this) { task ->
                        if (task.isSuccessful) {
                            val userId = auth.currentUser?.uid ?: return@addOnCompleteListener
                            val userMap = hashMapOf(
                                "username" to username, "email" to email
                            )
                            firestore.collection("users").document(userId).set(userMap)
                                .addOnSuccessListener {
                                    Toast.makeText(
                                        this, "Регистрация прошла успешно!", Toast.LENGTH_SHORT
                                    ).show()
                                    finish()
                                }.addOnFailureListener { e ->
                                    Toast.makeText(
                                        this, "Ошибка сохранения: ${e.message}", Toast.LENGTH_SHORT
                                    ).show()
                                }
                        } else {
                            Toast.makeText(
                                this,
                                "Ошибка регистрации: ${task.exception?.message}",
                                Toast.LENGTH_SHORT
                            ).show()
                        }
                    }
            } else {
                Toast.makeText(
                    this,
                    "Неверный формат пароля",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }
    }

    private fun isPasswordValid(password: String): Boolean {
        // Минимальная длина - 8 символов
        if (password.length < 8) return false
        // Проверка на заглавные и строчные буквы, цифры и спецсимволы
        val hasUpperCase = password.any { it.isUpperCase() }
        val hasLowerCase = password.any { it.isLowerCase() }
        val hasDigit = password.any { it.isDigit() }
        return hasUpperCase && hasLowerCase && hasDigit
    }
}