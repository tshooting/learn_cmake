# coding=UTF-8
import xlrd


def read_xlsx(path):
    workbook = xlrd.open_workbook(path)
    sheet1 = workbook.sheet_by_index(0)
    rows = sheet1.nrows
    cols = sheet1.ncols
    print(cols)
    for i in range(1, rows):
        stri_0 = sheet1.cell_value(i, int(0))
        stri_1 = sheet1.cell_value(i, int(1))
        stri_2 = sheet1.cell_value(i, int(2))
        stri_3 = str(sheet1.cell_value(i, int(3)))

        ans = stri_1[0:-2] + ". " + stri_0 + ". "
        if len(stri_2) > 1 and stri_3 != None and int(len(stri_3)) > 1:
            ans = ans + stri_2 + ", " + stri_3[0:-2] + "."
        elif stri_3 != None and int(len(stri_3)) > 1:
            ans = ans + stri_3[0:-2] + "."

        print(ans)
        # for j in range(2, cols):
        #     stri_j = sheet1.cell_value(i, j)
        #     if stri_j != None:
        #         ans = stri_j
        # print(ans)


def read_xlsx_replace(path):
    workbook = xlrd.open_workbook(path)
    sheet1 = workbook.sheet_by_index(0)
    rows = sheet1.nrows
    cols = sheet1.ncols
    print(rows)
    for i in range(46, rows):
        stri_0 = str(i + 1) + "_" + sheet1.cell_value(i, int(0)).replace(
            ' ', '_')
        print(stri_0)
    #     stri_1 = sheet1.cell_value(i, int(1))
    #     stri_2 = sheet1.cell_value(i, int(2))
    #     stri_3 = str(sheet1.cell_value(i, int(3)))

    #     ans = stri_1[0:-2] + ". " + stri_0 + ". "
    #     if len(stri_2) > 1 and stri_3 != None and int(len(stri_3)) > 1:
    #         ans = ans + stri_2 + ", " + stri_3[0:-2] + "."
    #     elif stri_3 != None and int(len(stri_3)) > 1:
    #         ans = ans + stri_3[0:-2] + "."


if __name__ == "__main__":
    file_path = "new_ref.xlsx"
    read_xlsx_replace(file_path)
    # string = "abca bcabc"
    # string = string.replace(' ', '+')
    # print(string)

    # my_str = ' b c d e'
    # my_str.replace(" ", "-")
    # print(my_str)
'''
47_Consistent_Monocular_Ackermann_Visual–Inertial_Odometry_for_Intelligent_and_Connected_Vehicle_Localization
48_A_Global_Occlusion-Aware_Approach_to_Self-Supervised_Monocular_Visual_Odometry
49_Improved_Bundle_Adjustment_Based_on_ADMM

50_Fusing_IMU_Data_into_SfM_for_Image-Based_3D_Reconstruction
51_An_Improved_Monocular_Visual-Inertial_Navigation_System
52_Architecture_générique_de_fusion_par_approche_Top-Down:_application_à_la_localisation_d’un_robot_mobile
53_Camera_Pose_Correction_in_SLAM_Based_on_Bias_Values_of_Map_Points
54_Confidence_analysis_of_feature_points_for_visual-inertial_odometry_of_urban_vehicles
55_Accurate_Visual-Inertial_SLAM_by_Feature_Re-identification
56_Adaptive_Real-Time_Loop_Closure_Detection_Based_on_Image_Feature_Concatenation
57_Factor_Graph-Based_Smoothing_Without_Matrix_Inversion_for_Highly_Precise_Localization
58_Calibration_and_Absolute_Pose_Estimation_of_Trinocular_Linear_Camera_Array_for_Smart_City_Applications
59_GNSS-Aided_Visual-Inertial_Odomtry_with_Failure_Mode_Recognition
60_Improved_Bundle_Adjustment_Based_on_ADMM
61_Algorithmes_de_lissage_pour_la_navigation,_la_localisation_et_la_cartographie,_basés_sur_des_capteurs_inertiels_haute_qualité
62_Aircraft_Autonomous_Positioning_Based_on_a_Coarse_to_Fine_Multi-modal_Image_Registration_Scheme
63_Improving_the_applicability_of_visual_SLAM_with_submodular_submatrix_selection
64_ROVTIO:_RObust_Visual_Thermal_Inertial_Odometry
65_Calibrating_3D_Scanner_in_the_Coordinate_System_of_Optical_Tracker_for_Image-To-Patient_Registration
66_LiDAR-Based_Glass_Detection_for_Improved_Occupancy_Grid_Mapping
67_Towards_Robust_Visual-Inertial_Estimation
68_Visual_inertial_odometry_and_lidar_inertial_odometry_for_mobile_robot
69_Dense_point_cloud_map_construction_based_on_stereo_VINS_for_mobile_vehicles
70_Multi-Feature_Nonlinear_Optimization_Motion_Estimation_Based_on_RGB-D_and_Inertial_Fusion
71_Multi-Modal_Neural_Feature_Fusion_for_Automatic_Driving_Through_Perception-Aware_Path_Planning
72_Multi-Modal_Neural_Feature_Fusion_for_Pose_Estimation_and_Scene_Perception_of_Intelligent_Vehicle
73_The_present_and_future_of_mixed_reality_in_China
74_Self-optimizing_loop_sifting_and_majorization_for_3D_reconstruction
75_Geometry_model_for_marker-based_localisation
76_A_Brief_Survey_of_Loop_Closure_Detection:_A_Case_for_Rethinking_Evaluation_of_Intelligent_Systems
77_GNSS_vulnerability_reliable_assessment_and_its_substitution_with_visual–inertial_navigation
78_Visual_and_Visual-Inertial_SLAM:_State_of_the_Art,_Classification,_and_Experimental_Benchmarking
79_Feature-based_SLAM_for_Dense_Mapping
80_The_software_tool_for_comparison_and_configuration_of_nonlinear_optimization_techniques_in_ORB-SLAM
81_Rotation_Matrix_Oriented_Visual_Inertial_Online_Initialization
82_Hierarchical_Segment-based_Optimization_for_SLAM
83_Markov_Parallel_Tracking_and_Mapping_for_Probabilistic_SLAM
84_Robust_Vision-Aided_Self-Localization_of_Mobile_Robots
85_Sampson_Distance:_A_New_Approach_to_Improving_Visual-Inertial_Odometry’s_Accuracy
86_LSFB:_A_Low-cost_and_Scalable_Framework_for_Building_Large-Scale_Localization_Benchmark
87_ROOAD:_RELLIS_Off-road_Odometry_Analysis_Dataset
88_Bridging_the_Gap_Between_Visual_Servoing_and_Visual_SLAM:_A_Novel_Integrated_Interactive_Framework
89_RISE-SLAM:_A_Resource-aware_Inverse_Schmidt_Estimator_for_SLAM
90_Sensor_Fusion_for_Robotic_Surface_and_Subsurface_Infrastructure_Inspection
91_Robust_6-DOF_Camera_Relocalization_in_Multi-view_Structure_from_Motion
92_Information_Theory_and_Probabilistic_Modeling_for_Robot_Localization
'''