package com.example.noam.kotelmania

import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity
import android.content.Context
import android.content.pm.PackageManager
import android.location.Location
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import android.util.Log
import com.google.android.gms.location.LocationCallback
import com.google.android.gms.location.LocationRequest
import com.google.android.gms.location.LocationResult
import com.google.android.gms.location.LocationServices

class LocationHelper (val context: Context, val destination : Location,
                      val onDestinationInteractionListener: OnDestinationInteractionListener)
    : LocationCallback(), ActivityCompat.OnRequestPermissionsResultCallback {


    val TAG = "LocationHelper"
    private val LOCATION_RQUESET_CODE = 101
    var fusedLocationClient = LocationServices.getFusedLocationProviderClient(context)

    init {
        setupPermissions()
        startLocationUpdates()
    }


    /** Permissions **/
    private fun checkPermissions() : Boolean {
        val finePermission = ContextCompat.checkSelfPermission(context,
                Manifest.permission.ACCESS_FINE_LOCATION)
        val coarsePermission = ContextCompat.checkSelfPermission(context,
                Manifest.permission.ACCESS_COARSE_LOCATION)
        return finePermission == PackageManager.PERMISSION_GRANTED
                && coarsePermission == PackageManager.PERMISSION_GRANTED
    }

    private fun setupPermissions() {
        if (!checkPermissions())
            requestPermissions()
    }

    private fun requestPermissions() {
        ActivityCompat.requestPermissions(context as Activity,
                arrayOf(Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_FINE_LOCATION),LOCATION_RQUESET_CODE                )
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        when (requestCode) {
            LOCATION_RQUESET_CODE -> {

                if (grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    Log.i(TAG, "Permission has been denied by user")
                } else {
                    Log.i(TAG, "Permission has been granted by user")
                    startLocationUpdates()
                }
            }
        }
    }
    /** Permissions **/

    private fun createLocationRequest(): LocationRequest {
        val locationRequest = LocationRequest().apply {
            interval = 10000
            fastestInterval = 5000
            priority = LocationRequest.PRIORITY_HIGH_ACCURACY
        }
        return locationRequest
    }

    @SuppressLint("MissingPermission")
    fun startLocationUpdates() {
        val locationRequest = createLocationRequest()
        if (checkPermissions())
        {
            fusedLocationClient.requestLocationUpdates(locationRequest, this, null /* Looper */)
        }
    }

    fun stopLocationUpdates() {
        if (checkPermissions())
        {
            fusedLocationClient.removeLocationUpdates(this)
        }
    }

    override fun onLocationResult(locationResult: LocationResult?) {
        locationResult ?: return
        for (location in locationResult.locations){
            val dst = location.distanceTo(destination)
            onDestinationInteractionListener.onLocationUpdate(location, dst)
            if (dst < 100)
                onDestinationInteractionListener.onDestinationReached()
            else
                onDestinationInteractionListener.onDestinationLeft()
        }
    }
}

interface OnDestinationInteractionListener{
    fun onDestinationReached()
    fun onDestinationLeft()
    fun onLocationUpdate(loc : Location, dst : Float)
}