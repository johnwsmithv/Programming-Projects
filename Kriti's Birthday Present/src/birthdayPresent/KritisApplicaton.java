/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// Importing packages 
package birthdayPresent;
import java.awt.Color;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.net.URL;
import java.io.IOException;
import externalLibraries.AsyncScalr;
import externalLibraries.Scalr;
import java.awt.image.BufferedImage;
/**
 *
 * @author John William Smith, V
 * For the Love of my life: Kriti Saxena
 */
public class KritisApplicaton extends javax.swing.JFrame {
    // A String array that contains image paths that hold significance for 
    // Kriti and John; the images are contained in the Image Folder
    private final String[] pictureList = {
        "partyWhereIMetKriti.JPG", "highWayPizzaStateCollege.jpg",
        "ourFirstPicTogether.png", "october20TheView.jpg",
        "halloween2019.JPG", "halloweenCostumesNov1.jpg",
        "dateAtIndianPlaceNov15.JPEG", "onTheBusNov15.JPEG",
        "kritiBeingSillyNov15.JPEG", "firstFootballGameTogetherNov16.JPEG",
        "afterFootballGameNov16.JPEG", "waitingForTheBusNov20.JPEG",
        "goingToTheMoviesDec20.JPEG", "firstPicInNYJan2.JPEG",
        "inFrontOfChristmasTreeJan2.JPEG", "inFrontOfBullJan2.JPEG",
        "sittingOnBenchJan2.JPEG", "sittingOnTheStairsJan2.JPEG",
        "onTheBoatStatueOfLibertyJan2.JPEG", "onTheBoatCityView.JPEG",
        "kritiBeingSillyWithFrenchFryJan2.JPEG", "rockefellerTreeJan2.JPEG",
        "rockefellerTree_1Jan2.JPEG", "rockefellerTree_2Jan2.JPEG",
        "buildingShowJan2.JPEG", "timeSquare_1Jan2.JPEG",
        "timeSquare_2Jan2.JPEG","busHomeJan2.JPEG",
        "johnAndKritiWatchingMovieJan18.JPEG", "jbAndKriiBeingSilliesJan23.JPEG",
        "kriiLookinHotAFJan25.JPEG", "secondDateAtIndianPavillion.JPEG",
        "kritiEatingFrosting.JPEG", "usTogether.JPG", "valentines_1.JPEG",
        "valentines_2.JPEG", "valentines_3.JPEG", "studying.JPEG", 
        "kriiAndJBBeingSilly.PNG", "spicyMexicanDish.JPEG", 
        "deliciousPizzas.JPEG", "soCute.JPEG", "jerseyCityOne.JPEG",
        "jerseyCityTwo.JPEG", "jerseyCityThree.JPEG", "iLoveYou.jpg"
    };
    // The corresponding descriptions of the following pics
    private final String[] pictureDescriptions = {
        "09/07/2019: This is the party where I met you at. I rememeber Jake sending us this "
            + "flyer and I was like oh cool! Let's go!\nAnd what do you know, "
            + "I'm fooling around in the pool and I see this beautiful girl;"
            + " I remember introducing myself and the rest is history.",
        "09/28/2019: High Way Pizza: this is where we had our first date; after weeks of "
            + "trying to get you to go out with me you finally said yes!\n"
            + "One this that we will never forget is the fact that we ate pizza"
            + " with a fork and a knife!",
        "10/19/2019: This was our first picture together at my place. If I "
            + "remember correctly, we were having some drinking! Whoops!",
        "10/19/2019: At your place and we were definitely cooking some good food!",
        "10/31/2019: I was studying for my EE 310 Test this night; you walked"
            + " into the library with your outfit on and my mouth dropped. "
            + "You looked drop dead gorgeous.",
        "11/01/2019: This was the night I had my EE Test. We got back to my place"
            + " and we got dressed in our costumes. This was the night that Danny "
            + "and everyone else came over and we drank some good stuff and played "
            + "Cards Against Humanity. This was a fun night.",
        "11/15/2019: I believe this is the first time we went to Indian Pavillion;"
            + " you looked absolutely beautiful; the food was delicious too!",
        "11/15/2019: We are on the bus being absolutely silly!",
        "11/15/2019: Krii is being sillies here!",
        "11/16/2019: Your first Penn State Football game, and our first game together;"
            + " man that was so cold, but it was good having you in my arms!)",
        "11/16/2019: After the Football game kiss!",
        "11/20/2019: Kriti with her McDonald's Coffee and John waiting for the NV!",
        "12/20/2019: The two of us waiting for the bus after missing the first "
            + "bus from being at the wrong bus stop! Whoops!",
        "01/02/2020: Our first pic in NYC together!",
        "01/02/2020: In front of the Christmas Tree on Wall Street!",
        "01/02/2020: We had to traverse the giant crowd to get this pic!",
        "01/02/2020: Two love birds sitting on a bench in the middle of NYC "
            + "doing some kissing and right before we bought our tickets to "
            + "the boat ride to see the Statue of Liberty!",
        "01/02/2020: Sitting on the stairs (in a mall I think), waiting for "
            + "our ride on the boat to come along!",
        "01/02/2020: After missing the first boat, we had to wait almost three "
            + "hours to get on a boat, but it was completely worth it; the view "
            + "was absolutely incredible and being on the boat with my love,"
            + " Kriti Saxena, made it even better.",
        "01/02/2020: A view of the city at night from a distance; this was so beautiful",
        "01/02/2020: Kriti was being silly here eating her favorite snack, McDonald's"
            + " french fries! Sillies!",
        "01/02/2020: Our first pic together in front of the Rockefeller Christmas Tree;"
            + " the tree was absolutely incredible and I couldn't be any happier!",
        "01/02/2020: Kissing in front of the Rockefeller Tree!",
        "01/02/2020: Kriti kissing John on the cheek!",
        "01/02/2020: Building show thingy that was so cool!",
        "01/02/2020: Us in Time Square! It was so beautiful.",
        "01/02/2020: Kissing in Time Square",
        "01/02/2020: The Bus ride home after an incredible day.",
        "01/18/2020: We were watching a movie togther and you were wearing your new jacket!",
        "01/23/2020: Us being sillies on the bus!",
        "01/25/2020: You were looking hot af; my jaw dropped. This is the night "
            + "when I picked you and Kathryn up from the club and you were pretty "
            + "under the influence; I had to change you and put you in my PJs! lmaooo",
        "02/07/2020: This is our second date at the Indian Pavillion; this was a lot of fun!",
        "02/08/2020: This is when we decided to finally build the ginger bread house "
            + "and that ended up being a lot of fun; you're being sillies and "
            + "eating the frosting!",
        "02/09/2020: JB and Krii being cute together!",
        "02/14/2020: When we both dressed up fancy af and you looked so hot",
        "02/14/2020: JB carrying Krii",
        "02/14/2020: JB took a funny pick of Krii :P",
        "02/15/2020: One of the many times when we went to the library to be studious!",
        "02/27/2020: JB and Krii being sillies while cooking!!!",
        "02/28/2020: When we cooked that spicy ass mexican food and neither of us could eat it lmaoo",
        "03/01/2020: The pizzas on the naan were sooooo goood!",
        "03/06/2020: Our last picture session together before we had dinner"
            + " with your mom and brother which was a total success; I love"
            + " you so much beautiful, and I cannot wait to make more memories"
            + " with you.",
        "06/19/2020: We finally got to see each other after a little more than three months"
            + " of being apart! You looked absolutely gorgeous in your dress!!",
        "06/19/2020: Krii and JB being cuties together!!",
        "06/19/2020: Look at us soooo cute!",
        "Foever And Always: Kriti you mean the absolute world to me and I cannot be more thankful"
            + " for you being in my life. You have brightend my world up so much and made me be"
            + " thankful for the life I have. You are the most stunning girl in the room, you"
            + " are the brightest and smartest girl in the room; you are everything a guy could ask for"
            + " and I cannot be any happier calling you mine. I cannot wait to begin our life"
            + " together beautiful. Next year when we move in together, we are going to have"
            + " the best life together and I cannot wait to spend it with you. We are going"
            + " to make so many memories together, and I'm so happy to be making them with you."
            + " I will love you forever and always. Your boyfriend (soon to be fiance and hubby),"
            + " your Johnny Boy.\nJohn William Smith, V"
    };
    private int photoIterator = 1;
    private int textIterator  = 1;
    /**
     * Creates new form KritisApplicaton
     */
    public KritisApplicaton() {
        initComponents();
        // Want to make sure that the parts that are supposed to be hidden are
        heartIcon.setVisible(true);
        backButton.setVisible(false);
        nextButton.setVisible(false);
        imageContainer.setVisible(false);
        pictureText.setVisible(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jInternalFrame2 = new javax.swing.JInternalFrame();
        jPanel2 = new javax.swing.JPanel();
        pictureText = new javax.swing.JTextArea();
        imageContainer = new javax.swing.JLabel();
        heartPanel = new javax.swing.JPanel();
        heartIcon = new javax.swing.JLabel();
        jScrollPane3 = new javax.swing.JScrollPane();
        noteToKriti1 = new javax.swing.JTextArea();
        nextButtonPanel = new javax.swing.JPanel();
        nextButton = new javax.swing.JLabel();
        backButton = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBackground(new java.awt.Color(216, 131, 172));
        setSize(new java.awt.Dimension(1920, 1080));

        jInternalFrame2.setBackground(new java.awt.Color(216, 131, 172));
        jInternalFrame2.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        jInternalFrame2.setMaximumSize(new java.awt.Dimension(1920, 1080));
        jInternalFrame2.setPreferredSize(new java.awt.Dimension(1920, 1080));
        jInternalFrame2.setVisible(true);

        jPanel2.setBackground(new java.awt.Color(216, 131, 172));

        pictureText.setColumns(20);
        pictureText.setFont(new java.awt.Font("Times New Roman", 0, 18)); // NOI18N
        pictureText.setLineWrap(true);
        pictureText.setRows(5);
        pictureText.setWrapStyleWord(true);

        imageContainer.setMaximumSize(new java.awt.Dimension(1000, 1000));
        imageContainer.setMinimumSize(new java.awt.Dimension(1000, 1000));

        heartPanel.setBackground(new java.awt.Color(216, 131, 172));

        heartIcon.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Icons/icons8_heart_outline_48px_1.png"))); // NOI18N
        heartIcon.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                heartIconMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout heartPanelLayout = new javax.swing.GroupLayout(heartPanel);
        heartPanel.setLayout(heartPanelLayout);
        heartPanelLayout.setHorizontalGroup(
            heartPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(heartPanelLayout.createSequentialGroup()
                .addGap(26, 26, 26)
                .addComponent(heartIcon)
                .addContainerGap(29, Short.MAX_VALUE))
        );
        heartPanelLayout.setVerticalGroup(
            heartPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(heartPanelLayout.createSequentialGroup()
                .addGap(26, 26, 26)
                .addComponent(heartIcon)
                .addContainerGap(26, Short.MAX_VALUE))
        );

        noteToKriti1.setEditable(false);
        noteToKriti1.setBackground(new java.awt.Color(64, 124, 196));
        noteToKriti1.setColumns(20);
        noteToKriti1.setFont(new java.awt.Font("Times New Roman", 0, 14)); // NOI18N
        noteToKriti1.setLineWrap(true);
        noteToKriti1.setRows(5);
        noteToKriti1.setText("Dear Kriti, \nThese past several months with you have been some of the best of my life. You and I have become an incredible couple and we have learned so much about life together. I am excited to continue this journey with you; when you're in California it is going to be rough, but we are going to get through it together! I can't wait until you move in with me in Willow Grove next year!\nI love you to the moon and back.\nJohn William Smith V\nP.S. Click that heart to the right of this wall of text for a surprise! ");
        noteToKriti1.setToolTipText("");
        noteToKriti1.setWrapStyleWord(true);
        noteToKriti1.setDragEnabled(true);
        noteToKriti1.setPreferredSize(new java.awt.Dimension(1920, 144));
        jScrollPane3.setViewportView(noteToKriti1);

        nextButtonPanel.setBackground(new java.awt.Color(216, 131, 172));

        nextButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Icons/icons8_next_page_30px.png"))); // NOI18N
        nextButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                nextButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout nextButtonPanelLayout = new javax.swing.GroupLayout(nextButtonPanel);
        nextButtonPanel.setLayout(nextButtonPanelLayout);
        nextButtonPanelLayout.setHorizontalGroup(
            nextButtonPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
            .addGroup(nextButtonPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(nextButtonPanelLayout.createSequentialGroup()
                    .addGap(35, 35, 35)
                    .addComponent(nextButton)
                    .addContainerGap(35, Short.MAX_VALUE)))
        );
        nextButtonPanelLayout.setVerticalGroup(
            nextButtonPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
            .addGroup(nextButtonPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(nextButtonPanelLayout.createSequentialGroup()
                    .addGap(35, 35, 35)
                    .addComponent(nextButton)
                    .addContainerGap(35, Short.MAX_VALUE)))
        );

        backButton.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Icons/backButton.png.png"))); // NOI18N
        backButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                backButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 616, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(heartPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(27, 27, 27))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel2Layout.createSequentialGroup()
                        .addComponent(backButton)
                        .addGap(82, 82, 82)))
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(pictureText)
                    .addComponent(imageContainer, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGap(56, 56, 56)
                .addComponent(nextButtonPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(7616, Short.MAX_VALUE))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 171, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(9, 9, 9)
                                .addComponent(heartPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(131, 131, 131)
                                .addComponent(backButton))
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addComponent(imageContainer, javax.swing.GroupLayout.PREFERRED_SIZE, 845, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(pictureText, javax.swing.GroupLayout.PREFERRED_SIZE, 225, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGap(367, 367, 367)
                        .addComponent(nextButtonPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(456, 456, 456))
        );

        imageContainer.getAccessibleContext().setAccessibleName("imageContainer");
        backButton.getAccessibleContext().setAccessibleName("backButton");

        javax.swing.GroupLayout jInternalFrame2Layout = new javax.swing.GroupLayout(jInternalFrame2.getContentPane());
        jInternalFrame2.getContentPane().setLayout(jInternalFrame2Layout);
        jInternalFrame2Layout.setHorizontalGroup(
            jInternalFrame2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jInternalFrame2Layout.createSequentialGroup()
                .addGap(0, 0, Short.MAX_VALUE)
                .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );
        jInternalFrame2Layout.setVerticalGroup(
            jInternalFrame2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jInternalFrame2Layout.createSequentialGroup()
                .addGap(0, 0, Short.MAX_VALUE)
                .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jInternalFrame2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jInternalFrame2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void nextButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_nextButtonMouseClicked
        try{
            File imagePath = new File("../src/Images/" + pictureList[photoIterator]);
            BufferedImage image = ImageIO.read(imagePath);
            BufferedImage scaledImage = Scalr.resize(image, 800);
            imageContainer.setIcon(new ImageIcon((Image)scaledImage));
            pictureText.setText(pictureDescriptions[textIterator]);
            photoIterator++;
            textIterator++;
            if(photoIterator >= pictureList.length){
                photoIterator = 0;
                textIterator  = 0;
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }//GEN-LAST:event_nextButtonMouseClicked

    private void heartIconMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_heartIconMouseClicked
        // TODO add your handling code here:
        imageContainer.setVisible((true));
        File imagePath = new File("../src/Images/" + pictureList[0]);
         try{
            BufferedImage image = ImageIO.read(imagePath);
            BufferedImage scaledImage = Scalr.resize(image, 800);
            imageContainer.setIcon(new ImageIcon((Image)scaledImage));
        } catch(IOException e){
            e.printStackTrace();
        }
        backButton.setVisible(true);
        nextButton.setVisible(true);
        pictureText.setVisible(true);
        pictureText.setText(pictureDescriptions[0]);
    }//GEN-LAST:event_heartIconMouseClicked

    private void backButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_backButtonMouseClicked
        try{
            photoIterator--;
            textIterator--;
            if(photoIterator <  0){
                photoIterator = pictureList.length - 1;
                textIterator  = pictureDescriptions.length - 1;
            }
            File imagePath = new File("../src/Images/" + pictureList[photoIterator]);
            BufferedImage image = ImageIO.read(imagePath);
            BufferedImage scaledImage = Scalr.resize(image, 800);
            imageContainer.setIcon(new ImageIcon((Image)scaledImage));
            //imageContainer.setSize(icon.getIconHeight(), icon.getIconWidth());
            pictureText.setText(pictureDescriptions[textIterator]);
        } catch(IOException e){
            e.printStackTrace();
        }
    }//GEN-LAST:event_backButtonMouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(KritisApplicaton.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(KritisApplicaton.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(KritisApplicaton.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(KritisApplicaton.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new KritisApplicaton().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel backButton;
    private javax.swing.JLabel heartIcon;
    private javax.swing.JPanel heartPanel;
    private javax.swing.JLabel imageContainer;
    private javax.swing.JInternalFrame jInternalFrame2;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JLabel nextButton;
    private javax.swing.JPanel nextButtonPanel;
    private javax.swing.JTextArea noteToKriti1;
    private javax.swing.JTextArea pictureText;
    // End of variables declaration//GEN-END:variables
}
