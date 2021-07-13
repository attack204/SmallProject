package com.example.soundwave.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.soundwave.adapters.SoundWaveMessageAdapter
import com.example.soundwave.databinding.FragmentSoundWaveMessageBinding
import com.example.soundwave.models.SoundWaveMessageViewModel


class SoundWaveMessageFragment : Fragment() {

    private var binding: FragmentSoundWaveMessageBinding? = null

    private val sharedViewModel: SoundWaveMessageViewModel by activityViewModels()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val fragmentBinding = FragmentSoundWaveMessageBinding.inflate(inflater, container, false)
        binding = fragmentBinding
        return fragmentBinding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        binding?.apply {
            lifecycleOwner = this@SoundWaveMessageFragment
            viewModel = sharedViewModel
            soundWaveMessageRecyclerView.adapter = SoundWaveMessageAdapter()
            soundWaveMessageRecyclerView.layoutManager = LinearLayoutManager(requireContext())
        }
    }
}