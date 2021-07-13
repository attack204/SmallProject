package com.example.soundwave.adapters

import androidx.fragment.app.Fragment
import androidx.viewpager2.adapter.FragmentStateAdapter
import com.example.soundwave.fragments.MailFragment
import com.example.soundwave.fragments.SoundWaveFragment
import com.example.soundwave.fragments.SoundWaveMessageFragment


class HomeViewPagerAdapter(
    fragment: Fragment
) : FragmentStateAdapter(fragment) {

    override fun getItemCount(): Int {
        // 在首页有3个fragment被用于TabLayout
        return 3
    }

    override fun createFragment(position: Int): Fragment {
        return when (position) {
            0 -> SoundWaveMessageFragment()
            1 -> MailFragment()
            else -> SoundWaveFragment()
        }
    }
}