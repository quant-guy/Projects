#!/bin/bash
PROJECT_NAME=test_neural_network
./${PROJECT_NAME} --N32_Propagate1                                       
./${PROJECT_NAME} --N32_Propagate2                                       
./${PROJECT_NAME} --N32_BackPropagate1                                   
./${PROJECT_NAME} --N32_BackPropagate2                                   
./${PROJECT_NAME} --NMS_Error                                            
./${PROJECT_NAME} --NMS_Propagate                                        
./${PROJECT_NAME} --NMS_BackPropagate                                    
./${PROJECT_NAME} --N32_Learning                                         
./${PROJECT_NAME} --N32_Learning2                                        
./${PROJECT_NAME} --NMS_Learning                                         
./${PROJECT_NAME} --NMS_Learning2
