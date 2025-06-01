package by.byak.points

import android.animation.Animator
import android.animation.AnimatorSet
import android.animation.ObjectAnimator
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.view.animation.AccelerateInterpolator
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.viewpager2.widget.ViewPager2
import com.google.android.material.bottomnavigation.BottomNavigationView
import com.google.firebase.auth.FirebaseAuth

class MainActivity : AppCompatActivity() {
    private lateinit var bottomNavigationView: BottomNavigationView
    private lateinit var viewPager: ViewPager2

    private lateinit var auth: FirebaseAuth
    private lateinit var animatedIcon: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        auth = FirebaseAuth.getInstance()
        animatedIcon = findViewById(R.id.animatedIcon)
        bottomNavigationView = findViewById(R.id.bottomNavigationView)

        bottomNavigationView.visibility = View.GONE

        if (auth.currentUser == null) {
            performAnimation()

        } else {
            initializeViewPager()
        }
    }

    private fun initializeViewPager() {
        viewPager = findViewById(R.id.viewPager)
        viewPager.adapter = ViewPagerAdapter(this)
        bottomNavigationView.visibility = View.VISIBLE
        animatedIcon.visibility = View.GONE

        viewPager.registerOnPageChangeCallback(object : ViewPager2.OnPageChangeCallback() {
            override fun onPageSelected(position: Int) {
                super.onPageSelected(position)
                bottomNavigationView.menu.getItem(position).isChecked = true
            }
        })

        bottomNavigationView.setOnNavigationItemSelectedListener { item ->
            when (item.itemId) {
                R.id.navigation_profile -> viewPager.currentItem = 0
                R.id.navigation_create_route -> viewPager.currentItem = 1
                R.id.navigation_routes -> viewPager.currentItem = 2
            }
            true
        }
    }


    private fun loadFragment(fragment: Fragment) {
        supportFragmentManager.beginTransaction().replace(R.id.container, fragment).commit()
        bottomNavigationView.visibility = View.VISIBLE
    }

    private fun performAnimation() {
        bottomNavigationView.visibility = View.GONE
        animatedIcon.visibility = View.VISIBLE

        // Анимация падения сверху вниз
        val screenHeight = resources.displayMetrics.heightPixels
        val dropAnimation = ObjectAnimator.ofFloat(
            animatedIcon, "translationY", -420f, screenHeight / 2f - 180f
        )
        dropAnimation.duration = 2000
        dropAnimation.interpolator = AccelerateInterpolator()

        // Анимация увеличения и исчезновения
        val scaleUpX = ObjectAnimator.ofFloat(animatedIcon, "scaleX", 1f, 3f)
        val scaleUpY = ObjectAnimator.ofFloat(animatedIcon, "scaleY", 1f, 3f)
        val fadeOut = ObjectAnimator.ofFloat(animatedIcon, "alpha", 1f, 0f)

        scaleUpX.duration = 1000
        scaleUpY.duration = 1000
        fadeOut.duration = 1000

        val animatorSet = AnimatorSet()

        dropAnimation.addListener(object : Animator.AnimatorListener {
            override fun onAnimationStart(animation: Animator) {}

            override fun onAnimationEnd(animation: Animator) {
                animatorSet.play(scaleUpX).with(scaleUpY).before(fadeOut)
                animatorSet.addListener(object : Animator.AnimatorListener {
                    override fun onAnimationEnd(animation: Animator) {
                        if (auth.currentUser == null) {
                            startActivity(Intent(this@MainActivity, LoginActivity::class.java))
                            finish()
                        } else {
                            loadFragment(ProfileFragment())
                        }
                        animatedIcon.visibility = View.GONE
                    }

                    override fun onAnimationStart(animation: Animator) {}
                    override fun onAnimationCancel(animation: Animator) {}
                    override fun onAnimationRepeat(animation: Animator) {}
                })
                animatorSet.start()
            }

            override fun onAnimationCancel(animation: Animator) {}
            override fun onAnimationRepeat(animation: Animator) {}
        })
        dropAnimation.start()
    }
}
