package com.example.soundwave.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.example.soundwave.R
import com.example.soundwave.adapters.HomeViewPagerAdapter
import com.example.soundwave.databinding.FragmentSoundWaveHostBinding
import com.google.android.material.bottomnavigation.BottomNavigationView
import com.google.android.material.tabs.TabLayoutMediator


class SoundWaveHostFragment : Fragment() {

    private var _binding: FragmentSoundWaveHostBinding? = null
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentSoundWaveHostBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        // 获取首页控件的引用
        val tabLayout = binding.homeTabLayout
        val viewPager = binding.homeViewPager

        // 实例化HomeViewPagerAdapter
        val adapter = HomeViewPagerAdapter(this@SoundWaveHostFragment)
        // 绑定适配器到home_view_pager控件
        viewPager.adapter = adapter

        /**
         * 一个可以将TabLayout和ViewPager绑定在一起的类
         * 使用attach链接，使用detach断开链接
         */
        TabLayoutMediator(tabLayout, viewPager) {
            tab, position -> when(position) {
                0 -> tab.text = "消息"
                1 -> tab.text = "音讯"
                else -> tab.text = "音波"
            }
        }.attach()

        /**
         * 底部导航栏的按钮监听器
         */
        BottomNavigationView.OnNavigationItemSelectedListener { item ->
            when(item.itemId) {
                R.id.page_sound_wave -> {
                    true
                }
                R.id.page_friend -> {
                    true
                }
                R.id.page_user -> {
                    true
                }
                else -> false
            }
        }
    }
}