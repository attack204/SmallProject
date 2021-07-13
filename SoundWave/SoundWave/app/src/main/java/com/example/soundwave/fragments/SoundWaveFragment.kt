package com.example.soundwave.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.GridLayoutManager
import com.example.soundwave.adapters.SoundWaveAdapter
import com.example.soundwave.databinding.FragmentSoundWaveBinding
import com.example.soundwave.models.SoundWaveViewModel


class SoundWaveFragment : Fragment() {

    private var binding: FragmentSoundWaveBinding? = null

    private val sharedViewModel: SoundWaveViewModel by activityViewModels()

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val fragmentBinding = FragmentSoundWaveBinding.inflate(inflater, container, false)
        binding = fragmentBinding
        return fragmentBinding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        binding?.apply {
            lifecycleOwner = this@SoundWaveFragment
            viewModel = sharedViewModel
            soundWaveRecyclerView.adapter = SoundWaveAdapter()
            soundWaveRecyclerView.layoutManager = GridLayoutManager(requireContext(), 2)
        }
    }
}